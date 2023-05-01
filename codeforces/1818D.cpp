#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<bool> vis(n+1,false),vis2(n+1,false);
    vector<int> pa(n+1);
    function<int(int,int)> dfs=[&](int u,int p){
        pa[u]=p;
        if(vis2[u])return u;
        if(vis[u])return 0;
        vis[u]=true;
        for(auto v:adj[u])if(v!=p){
            int res=dfs(v,u);
            if(res)return res;
        }
        return 0;
    };
    for(int i=1;i<=n;i++){
        if(adj[i].size()<4)continue;
        vis=vis2=vector<bool>(n+1,false);
        pa=vector<int>(n+1);
        for(auto v:adj[i])vis2[v]=true;
        for(auto v:adj[i]){
            vis2[v]=false;
            int res=dfs(v,i);
            vis2[v]=true;
            if(res){
                vector<pair<int,int>> ans;
                ans.emplace_back(i,res);
                int u=res;
                vector<bool> used(n+1);
                while(!used[u]){
                    ans.emplace_back(u,pa[u]);
                    u=pa[u];
                }
                int cnt=0;
                for(auto w:adj[i]){
                    if(w==v||w==res)continue;
                    cnt++;
                    if(cnt<=2)ans.emplace_back(i,w);
                }
                cout << "YES\n";
                cout << ans.size() << "\n";
                for(auto [x,y]:ans)cout << x << " " << y << "\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}