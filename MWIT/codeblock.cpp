#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> adj(n);
    for(auto &x:a)cin >> x;
    int u,v;
    for(int i=1;i<n;i++){
        cin >> u >> v;
        u--,v--;
        adj[u].push_back(v);
    }
    function<void(int u)> dfs=[&](int u){
        cout << a[u] << ' ';
        for(auto v:adj[u])dfs(v);
    };
    dfs(u);
}