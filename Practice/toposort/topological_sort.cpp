#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
queue<int> q;
vector<int> ans;
vector<int> adj[N];
int degin[N];

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for(int i=0;i<m;i++){
		int u,v;
		cin >> u >> v;
		adj[u].push_back(v);
		degin[v]++;
	}
	for(int i=1;i<=n;i++)if(degin[i])q.push(i);
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(auto v:adj[u]){
			degin[u]--;
			if(degin[u]==0)q.push(u);
		}
	}
	if(ans.size()<n)cout << -1;
	else for(auto i:ans)cout << i << ' ';
}