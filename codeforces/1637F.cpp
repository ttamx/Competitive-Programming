#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return a[i]<a[j];
    });
    vector<bool> mark(n),vis(n);
    ll ans=a[ord[n-1]]*2;
    for(int _i=0;_i<n-1;_i++){
        int i=ord[_i];
        mark[i]=true;
        if(deg[i]>1)continue;
        int u=i;
        while(deg[u]==1&&mark[u]){
            for(auto v:adj[u]){
                if(!vis[v]){
                    vis[u]=true;
                    deg[v]--;
                    u=v;
                    break;
                }
            }
        }
        if(deg[u]>1){
            ans+=a[i];
        }
    }
    cout << ans << "\n";
}