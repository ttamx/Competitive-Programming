#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    int ans=(1<<30)-1;
    for(int b=1<<29;b>0;b>>=1){
        int mask=ans^b;
        vector<bool> vis(n);
        queue<int> q;
        q.emplace(0);
        vis[0]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto [v,w]:adj[u]){
                if(!vis[v]&&w==(w&mask)){
                    q.emplace(v);
                    vis[v]=true;
                }
            }
        }
        if(vis[n-1])ans^=b;
    }
    cout << ans << "\n";
}