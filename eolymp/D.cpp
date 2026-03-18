#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
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
        if(n<=2){
            cout << n-1 << "\n";
            continue;
        }
        int tot=0;
        for(int i=0;i<n;i++){
            if(adj[i].size()==1){
                tot++;
            }
        }
        int ans=0;
        function<int(int,int)> dfs=[&](int u,int p){
            int s=(adj[u].size()==1);
            for(auto v:adj[u]){
                if(v==p)continue;
                int t=dfs(v,u);
                s+=t;
                if(tot-t+(adj[u].size()==2)==t+(adj[v].size()==2)){
                    ans++;
                }
            }
            return s;
        };
        for(int i=0;i<n;i++){
            if(adj[i].size()>1){
                dfs(i,-1);
                break;
            }
        }
        cout << ans << "\n";
    }
}