#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll c;
    cin >> n >> c;
    vector<vector<int>> adj(n);
    ll ans=0;
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        ans+=w;
    }
    vector<int> a;
    function<void(int,int)> dfs=[&](int u,int p){
        if(adj[u].size()%2){
            a.emplace_back(u);
        }
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
        }
    };
    dfs(0,-1);
    ans+=a.size()/2*c;
    cout << ans << " " << a.size()/2 << "\n";
    for(int i=0;i<a.size();i+=2){
        cout << a[i]+1 << " " << a[i+1]+1 << "\n";
    }
}