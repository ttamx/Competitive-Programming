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
    if(n<=3){
        cout << "Yes\n";
        exit(0);
    }
    vector<int> a(n);
    vector<bool> del(n);
    function<void(int,int)> dfs=[&](int u,int p){
        if(adj[u].size()>2)return;
        del[u]=true;
        for(auto v:adj[u]){
            if(v!=p){
                dfs(v,u);
            }
        }
    };
    for(int i=0;i<n;i++){
        if(adj[i].size()==1){
            dfs(i,-1);
        }
    }
    for(int i=0;i<n;i++){
        if(!del[i]){
            for(auto j:adj[i]){
                if(del[j]){
                    a[i]++;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        if(del[i])continue;
        int cnt=0;
        for(auto j:adj[i]){
            if(!del[j]&&adj[j].size()-min(a[j],2)>1){
                cnt++;
            }
        }
        if(cnt>2){
            cout << "No\n";
            exit(0);
        }
    }
    cout << "Yes\n";
}