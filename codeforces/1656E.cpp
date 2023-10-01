#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n+2);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    queue<int> q;
    vector<int> ans(n+2);
    ans[1]=adj[1].size();
    q.emplace(1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(ans[v])continue;
            ans[v]=adj[v].size()*(ans[u]<0?1:-1);
            q.emplace(v);
        }
    }
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}