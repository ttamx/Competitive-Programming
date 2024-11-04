#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> tin(n),tout(n),dep(n);
    int timer=-1;
    vector<array<int,2>> nim(n);
    function<void(int,int)> dfs=[&](int u,int p){
        tin[u]=timer++;
        nim[u][1]=a[u];
        for(auto v:adj[u]){
            if(v==p)continue;
            dep[v]=dep[u]^1;
            dfs(v,u);
            nim[u][0]^=nim[v][1];
            nim[u][1]^=nim[v][0];
        }
        tout[u]=timer;
    };
    dfs(0,-1);
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(tin[u]<=tin[v]&&tout[v]<=tout[u]){
            cout << "INVALID\n";
            continue;
        }
        if(dep[u]!=dep[v]){
            cout << (nim[0][0]>0?"YES":"NO") << "\n";
        }else{
            cout << ((nim[0][0]^nim[u][0]^nim[u][1])>0?"YES":"NO") << "\n";
        }
    }
}