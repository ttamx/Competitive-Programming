#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    vector<int> a;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        adj[max(x,0)].emplace_back(i);
    }
    function<int(int)> dfs=[&](int u){
        int res=0;
        for(auto v:adj[u])res=max(res,dfs(v)+1);
        return res;
    };
    cout << dfs(0) << "\n";
}