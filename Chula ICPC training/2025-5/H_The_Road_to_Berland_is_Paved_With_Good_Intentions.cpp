#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n*2);
    auto link=[&](int u,int v,int w){
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    };
    for(int i=0;i<n;i++){
        link(i,i+n,1);
    }
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        if(w){
            link(u,v,0);
            link(u+n,v+n,0);
        }else{
            link(u,v+n,0);
            link(u+n,v,0);
        }
    }
    vector<int> col(2*n,-1);;
    function<void(int)> dfs=[&](int u){
        for(auto [v,w]:adj[u]){
            if(col[v]==-1){
                col[v]=col[u]^w;
                dfs(v);
            }else if(col[v]!=(col[u]^w)){
                cout << "Impossible\n";
                exit(0);
            }
        }
    };
    for(int i=0;i<2*n;i++){
        if(col[i]==-1){
            col[i]=0;
            dfs(i);
        }
    }
    vector<int> ans;
    for(int i=0;i<n;i++){
        if(col[i]){
            ans.emplace_back(i);
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}