#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    vector<int> mark(n);
    queue<int> q;
    for(int i=0;i<n;i++){
        if(deg[i]==1){
            q.emplace(i);
        }
    }
    vector<ll> sz(n,1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        mark[u]=true;
        for(auto v:adj[u]){
            sz[v]+=sz[u];
            if(--deg[v]==1){
                q.emplace(v);
            }
        }
    }
    ll ans=1LL*n*(n-1);
    for(int i=0;i<n;i++){
        if(!mark[i]){
            ans-=sz[i]*(sz[i]-1)/2;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}