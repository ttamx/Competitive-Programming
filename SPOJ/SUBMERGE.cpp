#include<bits/stdc++.h>

using namespace std;

const int N=1e4+5;

int idx=1;
int disc[N],low[N];
vector<int> adj[N];
set<int> art;

void dfs(int u,int p){
	low[u]=disc[u]=idx++;
	int ch=0;
	for(auto v:adj[u]){
		if(v==p)continue;
		if(!disc[v]){
			ch++;
			dfs(v,u);
			low[u]=min(low[u],low[v]);
			if((p!=-1 and low[v]>=disc[u])or(p==-1 and ch>1))art.insert(u);
		}
		else{
			low[u]=min(low[u],disc[v]);
		}
	}
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	while(true){
		int n,m;
		cin >> n >> m;
		if(n==0 and m==0)break;
		idx=1;
		art.clear();
		for(int i=1;i<=n;i++){
			adj[i].clear();
			disc[i]=low[i]=0;
		}
		for(int i=0;i<m;i++){
			int u,v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		dfs(1,-1);
		cout << art.size() << '\n';
	}
}