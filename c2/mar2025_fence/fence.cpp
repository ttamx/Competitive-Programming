#include "fence.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=200005;
const int LG=19;
const int INF=INT_MAX/2;

int n,m;
ll a[N];
int p[N],id[N];
vector<int> adj[N];
int disc[N];
int timer=0;

struct DS{
	map<int,pair<int,int>> dat;
	DS(){dat[INF]={-INF,0};}
	void set(int l,int r,int v){
		auto it=dat.lower_bound(l);
		if(it->second.first<l){
			dat[l-1]=it->second;
			it->second.first=l;
		}
		while(it!=dat.end()&&it->first<=r)it=dat.erase(it);
		if(it!=dat.end()&&it->second.first<=r)it->second.first=r+1;
		dat[r]={l,v};
	}
	int get(int i){return dat.lower_bound(i)->second.second;}
}ds;

struct RMQ{
	ll t[LG][3*N];
	void set(int i,ll v){t[0][i]=v;}
	void build(){
		for(int i=1;i<LG;i++)for(int j=1,k=1+(1<<(i-1));k<=timer;j++,k++){
			t[i][j]=min(t[i-1][j],t[i-1][k]);
		}
	}
	ll query(int l,int r){
		if(l>r)swap(l,r);
		int k=31-__builtin_clz(r-l+1);
		return min(t[k][l],t[k][r-(1<<k)+1]);
	}
}rmq;

void dfs(int u){
	disc[u]=++timer;
	rmq.set(timer,a[u]);
	for(auto v:adj[u]){
		a[v]+=a[u];
		dfs(v);
		rmq.set(++timer,a[u]);
	}
}

void init(int _n,int _m,vector<vector<int>> LL,vector<vector<int>> UR,vector<int> H,vector<vector<int>> P) {   
	n=_n,m=_m;
	vector<tuple<int,int,int,int>> ev;
	for(int i=1;i<=n;i++){
		int x1=LL[i-1][0],y1=LL[i-1][1],x2=UR[i-1][0],y2=UR[i-1][1];
		ev.emplace_back(x1,i,y1,y2);
		ev.emplace_back(x2+1,-i,y1,y2);
		a[i]=H[i-1];
	}
	for(int i=0;i<m;i++){
		int x=P[i][0],y=P[i][1];
		ev.emplace_back(x,n+i+1,y,y);
	}
	sort(ev.begin(),ev.end());
	for(auto [x,i,y1,y2]:ev){
		if(i<0){
			ds.set(y1,y2,p[-i]);
		}else if(i<=n){
			p[i]=ds.get(y1);
			ds.set(y1,y2,i);
		}else{
			id[i-n]=ds.get(y1);
		}
	}
	for(int i=1;i<=n;i++)adj[p[i]].emplace_back(i);
	dfs(0);
	rmq.build();
}

ll ask(int u,int v){
	u=id[u+1],v=id[v+1];
  	return a[u]+a[v]-2*rmq.query(disc[u],disc[v]);
}