#include<bits/stdc++.h>

using namespace std;

const int N=705;

int idx=1;
int disc[N],low[N];
vector<int> adj[N];
set<pair<int,int>> bridge;

void dfs(int u,int p){
	disc[u]=idx++;
	low[u]=disc[u];
	int ch=0;
	for(auto v:adj[u]){
		if(v==p)continue;
		if(!disc[v]){
			ch++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>disc[u])bridge.insert({min(u,v),max(u,v)});
		}else{
			low[u]=min(low[u],disc[v]);
		}
	}
}

void runcase(){
	int n,m;
	cin >> n >> m;
	idx=1;
	bridge.clear();
	for(int i=1;i<=n;i++){
		disc[i]=low[i]=0;
		adj[i].clear();
	}
	for(int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	dfs(1,-1);
	if(bridge.empty())cout << "Sin bloqueos\n";
	else{
		cout << bridge.size() << '\n';
		for(auto [u,v]:bridge){
			cout << u << " " << v << '\n';
		}
	}
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	for(int i=1;i<=t;i++){
		cout << "Caso #" << i << '\n';
		runcase();
	}
}