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
        for(int i=1;i<n;i++){
            int u,v;
            cin >> u >> v;
            u--,v--;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        vector<int> dep(n);
        function<void(int,int)> dfs=[&](int u,int p){
            for(auto v:adj[u]){
                if(v==p){
                    continue;
                }
                dep[v]=dep[u]+1;
                dfs(v,u);
            }
        };
        dfs(0,-1);
        int rt=max_element(dep.begin(),dep.end())-dep.begin();
        dep[rt]=1;
        dfs(rt,-1);
        int dia=*max_element(dep.begin(),dep.end());
        cout << (dia%3==0?"Neodoomer":"Go8") << "\n";
    }
}