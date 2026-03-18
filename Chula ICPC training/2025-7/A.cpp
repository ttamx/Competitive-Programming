#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> deg(51);
    vector<vector<pair<int,int>>> adj(51);
    vector<bool> used(n);
    for(int i=0;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
        deg[u]++,deg[v]++;
    }
    int cnt=0;
    int root=-1;
    for(int i=1;i<=50;i++){
        if(deg[i]%2==1){
            cout << "some beads may be lost\n";
            return;
        }else if(deg[i]>0){
            root=i;
        }
    }
    vector<int> ptr(51);
    vector<pair<int,int>> ans;
    function<void(int)> dfs=[&](int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            auto [v,j]=adj[u][i];
            if(!used[j]){
                used[j]=true;
                dfs(v);
                ans.emplace_back(v,u);
            }
        }
    };
    dfs(root);
    if(ans.size()!=n){
        cout << "some beads may be lost\n";
        return;
    }
    for(auto [u,v]:ans){
        cout << u << " " << v << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << "\n";
        runcase();
        if(i<t)cout << "\n";
    }
}