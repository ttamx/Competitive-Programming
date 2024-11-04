#include "marbletracks.h"
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int deg[N];
vector<int> adj[N];
vector<tuple<int,int,int>> qrs[N];
int sz[N],hv[N],tin[N],tout[N],node[N],dep[N];
int timer=0;
vector<int> ans;
vector<int> comp[N];
bool vis[N];

struct Fenwick{
	int t[N];
	void update(int i,int v){
		for(i++;i<N;i+=i&-i)t[i]+=v;
	}
	int query(int i){
		int res=0;
		for(i=min(i+1,N-1);i>0;i-=i&-i)res+=t[i];
		return res;
	}
	int query(int l,int r){
		return query(r)-query(l-1);
	}
}fw;

struct CDQ{
	struct Query{
		int x,y,t,v,l,r;
		Query(int _x,int _y,int _t,int _v,int _l,int _r)
			:x(_x),y(_y),t(_t),v(_v),l(_l),r(_r){}
		bool operator<(const Query &o)const{
			return t<o.t;
		}
	};
	int timer;
	vector<Query> a,b;
	vector<int> ans;
	void init(){
		timer=0,q=0;
		a.clear();
		b.clear();
		ans.clear();
	}
	void update(int x,int y,int v){
		a.emplace_back(Query(x,y,timer++,v,-1,-1));
	}
	int query(int x,int l,int r){
		int v=ans.size();
		a.emplace_back(Query(x,-1,timer++,v,l,r));
		ans.emplace_back(0);
		return v;
	}
	void dnc(int l,int r){
		if(l==r)return;
		int m=(l+r)/2;
		dnc(l,m);
		dnc(m+1,r);
		vector<pair<int,int>> upd;
		for(int i=l,j=m+1,p=l;p<=r;p++){
			if(j>r||(i<=m&&a[i].x<=a[j].x)){
				b[p]=a[i];
				if(a[i].y!=-1){
					fw.update(a[i].y,a[i].v);
					upd.emplace_back(a[i].y,a[i].v);
				}
				i++;
			}else{
				b[p]=a[j];
				if(a[j].y==-1){
					ans[a[j].v]+=fw.query(a[j].l,a[j].r);
				}
				j++;
			}
		}
		for(int i=l;i<=r;i++){
			a[i]=b[i];
		}
		for(auto [i,v]:upd){
			fw.update(i,-v);
		}
	}
	void solve(){
		b=a;
		sort(a.begin(),a.end());
		dnc(0,timer-1);
	}
}cdq;

void dfs(int u,int rt){
	sz[u]=1;
	hv[u]=-1;
	tin[u]=++timer;
	node[timer]=u;
	comp[rt].emplace_back(dep[u]);
	for(auto v:adj[u]){
		dep[v]=dep[u]+1;
		dfs(v,rt);
		sz[u]+=sz[v];
		if(hv[u]==-1||sz[v]>sz[hv[u]]){
			hv[u]=v;
		}
	}
	tout[u]=timer;
}

void sack(int u,bool del){
	for(auto v:adj[u]){
		if(v!=hv[u]){
			sack(v,true);
		}
	}
	if(hv[u]!=-1){
		sack(hv[u],false);
	}
	fw.update(dep[u],+1);
	for(auto v:adj[u]){
		if(v!=hv[u]){
			for(int i=tin[v];i<=tout[v];i++){
				fw.update(dep[node[i]],+1);
			}
		}
	}
	for(auto [l,r,i]:qrs[u]){
		ans[i]=fw.query(dep[u]+l,dep[u]+r);
	}
	if(del){
		for(int i=tin[u];i<=tout[u];i++){
			fw.update(dep[node[i]],-1);
		}
	}
}

vector<int> observe(int _n,int _q,vector<int> a,vector<tuple<int,int,int>> queries){
	n=_n,q=_q;
	ans.resize(q);
	for(int i=0;i<q;i++){
		auto [s,l,r]=queries[i];
		qrs[s].emplace_back(l,r,i);
	}
	for(auto x:a){
		deg[x]++;
	}
	queue<int> qu;
	for(int i=0;i<n;i++){
		if(deg[i]==0){
			qu.emplace(i);
		}
	}
	while(!qu.empty()){
		int u=qu.front();
		qu.pop();
		vis[u]=true;
		adj[a[u]].emplace_back(u);
		deg[a[u]]--;
		if(deg[a[u]]==0){
			qu.emplace(a[u]);
		}
	}
	for(int i=0;i<n;i++){
		if(!vis[i]){
			dfs(i,i);
			sack(i,true);
		}
	}
	for(int st=0;st<n;st++){
		if(vis[st])continue;
		vector<int> cycle;
		for(int u=st;!vis[u];u=a[u]){
			vis[u]=true;
			cycle.emplace_back(u);
		}
		int csz=cycle.size();
		vector<tuple<int,int,int>> event;
		cdq.init();
		for(int i=0;i<csz;i++){
			int u=cycle[i];
			for(auto t:comp[u]){
				cdq.update(t-i,(t-i+csz)%csz,+1);
			}
		}
		for(int i=0;i<csz;i++){
			int u=cycle[i];
			for(auto t:comp[u]){
				cdq.update(t-i,(t-i+csz)%csz,-1);
			}
			for(auto t:comp[u]){
				cdq.update(t-i-csz,(t-i+csz)%csz,+1);
			}
			for(auto [l,r,j]:qrs[u]){
				ans[j]=0;
				l-=csz+i,r-=csz+i;
				event.emplace_back(j,cdq.query(r,0,csz-1),+1);
				event.emplace_back(j,cdq.query(l-1,0,csz-1),-1);
				if(r-l+1>=csz){
					event.emplace_back(j,cdq.query(l-1,0,csz-1),+1);
				}else{
					int cl=(l+2*csz)%csz,cr=(r+2*csz)%csz;
					assert(cl>=0&&cr>=0);
					if(cl<=cr){
						event.emplace_back(j,cdq.query(l-1,cl,cr),+1);
					}else{
						event.emplace_back(j,cdq.query(l-1,0,cr),+1);
						event.emplace_back(j,cdq.query(l-1,cl,csz-1),+1);
					}
				}
			}
		}
		cdq.solve();
		for(auto [i,j,mul]:event){
			ans[i]+=cdq.ans[j]*mul;
		}
	}
	return ans;
}
