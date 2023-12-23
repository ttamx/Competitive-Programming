#include "werewolf.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=2e5+5;

int n,m,q;
vector<int> adj[N];
bool vis[N];
int pos[N];
int s[N],e[N],l[N],r[N];
vector<int> ql[N],qr[N];
p2 ranl[N],ranr[N];

struct dsu_t{
	int p[N],l[N],r[N];
	void init(){
		for(int i=0;i<n;i++){
			p[i]=l[i]=r[i]=i;
		}
	}
	int fp(int u){
		if(u==p[u])return u;
		return p[u]=fp(p[u]);
	}
	void uni(int u,int v){
		u=fp(u),v=fp(v);
		if(u==v)return;
		p[v]=u;
		l[u]=min(l[u],l[v]);
		r[u]=max(r[u],r[v]);
	}
}dsu;

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
	int nxt=0;
	for(int i=0;i<n;i++)if(adj[i].size()==1)nxt=i;
	for(int i=0;i<n;i++){
		pos[nxt]=i;
		vis[nxt]=true;
		for(auto v:adj[nxt])if(!vis[v])nxt=v;
	}
	dsu.init();
	for(int u=n-1;u>=0;u--){
		for(auto v:adj[u]){
			if(v<u)continue;
			dsu.uni(pos[u],pos[v]);
		}
		for(auto i:ql[u]){
			int p=dsu.fp(pos[s[i]]);
			ranl[i]=p2(dsu.l[p],dsu.r[p]);
		}
	}
	dsu.init();
	for(int u=0;u<n;u++){
		for(auto v:adj[u]){
			if(v>u)continue;
			dsu.uni(pos[u],pos[v]);
		}
		for(auto i:qr[u]){
			int p=dsu.fp(pos[e[i]]);
			ranr[i]=p2(dsu.l[p],dsu.r[p]);
		}
	}
	vector<int> ans(q);
	for(int i=0;i<q;i++){
		int lb=max(ranl[i].first,ranr[i].first);
		int ub=min(ranl[i].second,ranr[i].second);
		ans[i]=lb<=ub;
	}
	return ans;
}