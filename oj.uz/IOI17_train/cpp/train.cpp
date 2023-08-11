#include "train.h"
#include<bits/stdc++.h>

using namespace std;

const int N=5005;

int n,m;
int all;
int a[N],cnt[N];
int deg[N];
bool vis[N],vis2[N],used[N];
vector<int> r;
vector<int> adj[N],rev[N];

vector<int> who_wins(vector<int> _a, vector<int> _r, vector<int> _u, vector<int> _v){
	n=_a.size();
	m=_u.size();
	all=n;
	for(int i=0;i<n;i++)a[i]=_a[i];
	for(int i=0;i<n;i++)if(_r[i])r.emplace_back(i);
	for(int i=0;i<m;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v);
		rev[v].emplace_back(u);
		deg[u]++;
	}
	vector<int> ans(n);
	while(all>0){
		vector<int> q;
		for(int i=0;i<n;i++){
			vis[i]=false;
			cnt[i]=0;
		}
		for(auto x:r){
			if(used[x])continue;
			q.emplace_back(x);
			vis[x]=true;
		}
		for(int i=0;i<q.size();i++){
			int u=q[i];
			for(auto v:rev[u]){
				if(vis[v]||used[v])continue;
				if(a[v]){
					vis[v]=true;
					q.emplace_back(v);
				}else if(++cnt[v]==adj[v].size()){
					vis[v]=true;
					q.emplace_back(v);
				}
			}
		}
		if(q.size()==all){
			for(auto x:q){
				ans[x]=1;
				used[x]=true;
				all--;
				for(auto v:rev[x])deg[v]--;
			}
			break;
		}
		vector<int> q2;
		for(int i=0;i<n;i++){
			vis2[i]=false;
			cnt[i]=0;
		}
		for(int i=0;i<n;i++){
			if(used[i])continue;
			if(!vis[i]){
				q2.emplace_back(i);
				vis2[i]=true;
			}
		}
		for(int i=0;i<q2.size();i++){
			int u=q2[i];
			for(auto v:rev[u]){
				if(vis2[v]||used[v])continue;
				if(!a[v]){
					vis2[v]=true;
					q2.emplace_back(v);
				}else if(++cnt[v]==deg[v]){
					vis2[v]=true;
					q2.emplace_back(v);
				}
			}
		}
		for(auto x:q2){
			ans[x]=0;
			used[x]=true;
			all--;
			for(auto v:rev[x])deg[v]--;
		}
	}
	return ans;
}