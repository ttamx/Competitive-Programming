#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        int n,m,k;
        cin >> n >> m >> k;
        if(n==0)break;
        vector<pair<int,int>> edges(k);
        vector<vector<int>> adj(n+m);
        for(auto &[u,v]:edges){
            cin >> u >> v;
            u--,v--;
            v+=n;
            adj[u].emplace_back(v);
        }
        vector<bool> vis(n+m);
        vector<int> match(n+m,-1),ptr(n+m);
        function<bool(int)> kuhn=[&](int u){
            if(vis[u])return false;
            vis[u]=true;
            for(int &i=ptr[u];i<adj[u].size();i++){
                int v=adj[u][i];
                if(match[v]==-1||kuhn(match[v])){
                    match[u]=v;
                    match[v]=u;
                    return true;
                }
            }
            return false;
        };
        int cnt=0;
        for(int i=0;i<n;i++){
            if(kuhn(i)){
                cnt++;
                vis.assign(n+m,false);
                ptr.assign(n+m,0);
            }
        }
        int s=n+m,t=n+m+1;
        vector<vector<int>> adj2(n+m+2);
        for(int i=0;i<n;i++){
            if(match[i]==-1){
                adj2[s].emplace_back(i);
            }else{
                adj2[i].emplace_back(s);
            }
        }
        for(int i=n;i<n+m;i++){
            if(match[i]==-1){
                adj2[i].emplace_back(t);
            }else{
                adj2[t].emplace_back(i);
            }
        }
        for(auto [u,v]:edges){
            adj2[u].emplace_back(v);
            if(match[u]==v){
                adj2[v].emplace_back(u);
            }
        }
        vector<bool> vis2(n+m+2);
        queue<int> q;
        q.emplace(s);
        vis2[s]=true;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj2[u]){
                if(!vis2[v]){
                    vis2[v]=true;
                    q.emplace(v);
                }
            }
        }
        cout << cnt << " ";
        for(int i=0;i<n;i++){
            if(!vis2[i]){
                cout << "r" << i+1 << " ";
            }
        }
        for(int i=n;i<n+m;i++){
            if(vis2[i]){
                cout << "c" << i+1-n << " ";
            }
        }
        cout << "\n";
    }
}