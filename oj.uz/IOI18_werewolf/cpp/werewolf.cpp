#include "werewolf.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=2e5+5;
const int M=4e5+5;
const int K=(1<<19)+5;

int n,m,q;
vector<int> adj[N];
int s[N],e[N],l[N],r[N];
vector<int> ql[N],qr[N];
vector<t3> ql2[N],qr2[N];
int pl[N],pr[N];
p2 ranl[N],ranr[N];
int posx[N],posy[N];
vector<int> num[N];

struct dsu_t{
	int p[M];
	int in[M],out[M],pos[M];
	vector<p2> node;
	void init(){
		for(int i=0;i<2*n;i++){
			p[i]=i;
		}
		node=vector<p2>(n,p2(-1,-1));
	}
	int fp(int u){
		if(u==p[u])return u;
		return p[u]=fp(p[u]);
	}
	void uni(int u,int v){
		u=fp(u),v=fp(v);
		if(u==v)return;
		int np=node.size();
		p[u]=p[v]=np;
		node.emplace_back(u,v);
	}
	void dfs(int u,int &t){
		if(u<n){
			in[u]=out[u]=++t;
			pos[t]=u;
			return;
		}
		auto [l,r]=node[u];
		dfs(l,t);
		dfs(r,t);
		in[u]=min(in[l],in[r]);
		out[u]=max(out[l],out[r]);
	}
	void dfs(){
		int t=0;
		dfs(node.size()-1,t);
	}
}dsu;

struct fenwick{
	int t[N];
	void add(int i,int v){
		while(i<N)t[i]+=v,i+=i&-i;
	}
	int read(int i){
		int res=0;
		while(i>0)res+=t[i],i-=i&-i;
		return res;
	}
}f;

vector<int> check_validity(int _n,vector<int> X,vector<int> Y,vector<int> S,vector<int> E,vector<int> L,vector<int> R) {
	n=_n;
	m=X.size();
	q=S.size();
	for(int i=0;i<m;i++){
		int u=X[i],v=Y[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	for(int i=0;i<q;i++){
		s[i]=S[i];
		e[i]=E[i];
		l[i]=L[i];
		r[i]=R[i];
		ql[l[i]].emplace_back(i);
		qr[r[i]].emplace_back(i);
	}
	dsu.init();
	for(int u=n-1;u>=0;u--){
		for(auto v:adj[u]){
			if(v<u)continue;
			dsu.uni(u,v);
		}
		for(auto i:ql[u]){
			pl[i]=dsu.fp(s[i]);
		}
	}
	dsu.dfs();
	for(int i=0;i<n;i++)posx[i]=dsu.in[i];
	for(int i=0;i<q;i++){
		int p=pl[i];
		ranl[i]=p2(dsu.in[p],dsu.out[p]);
	}
	dsu.init();
	for(int u=0;u<n;u++){
		for(auto v:adj[u]){
			if(v>u)continue;
			dsu.uni(u,v);
		}
		for(auto i:qr[u]){
			pr[i]=dsu.fp(e[i]);
		}
	}
	dsu.dfs();
	for(int i=0;i<n;i++)posy[i]=dsu.in[i];
	for(int i=0;i<q;i++){
		int p=pr[i];
		ranr[i]=p2(dsu.in[p],dsu.out[p]);
	}
	for(int i=0;i<n;i++)num[posx[i]].emplace_back(posy[i]);
	vector<int> ans(q);
	for(int i=0;i<q;i++){
		auto [x,y]=ranl[i];
		auto [a,b]=ranr[i];
		ql2[x-1].emplace_back(a,b,i);
		qr2[y].emplace_back(a,b,i);
	}
	for(int i=1;i<=n;i++){
		for(auto x:num[i])f.add(x,1);
		for(auto [a,b,id]:ql2[i])ans[id]-=f.read(b)-f.read(a-1);
		for(auto [a,b,id]:qr2[i])ans[id]+=f.read(b)-f.read(a-1);
	}
	for(int i=0;i<q;i++)ans[i]=ans[i]>0;
	return ans;
}