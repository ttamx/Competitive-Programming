#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> dep(n),par(n);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            if(v!=par[u]){
                par[v]=u;
                dep[v]=dep[u]+1;
                dfs(v);
            }
        }
    };
    dfs(0);
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(int i=0;i+1<n;i++){
        if(dep[a[i]]>dep[a[i+1]]){
            cout << "No\n";
            exit(0);
        }
    }
    vector<int> ord(n);
    for(int i=0;i<n;i++)ord[a[i]]=i;
    for(int i=1;i+1<n;i++){
        if(dep[a[i]]==dep[a[i+1]]&&ord[par[a[i]]]>ord[par[a[i+1]]]){
            cout << "No\n";
            exit(0);
        }
    }
    cout << "Yes\n";
}