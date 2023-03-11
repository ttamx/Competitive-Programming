#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> p(n);
    for(auto &x:p)cin >> x,x--;
    vector<bool> vis(n);
    function<int(int)> dfs=[&](int u){
        if(vis[u])return 0;
        vis[u]=true;
        return dfs(p[u])+1;
    };
    int ans=0;
    for(int i=0;i<n;i++)ans=max(ans,dfs(i));
    cout << ans;
}