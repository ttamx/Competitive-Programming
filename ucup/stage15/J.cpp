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
        vector<pair<int,int>> path;
        vector<int> dep(n),par(n,-1);
        function<int(int)> dfs=[&](int u){
            bool ok=false;
            int s=-1;
            for(auto v:adj[u])if(v!=par[u]){
                par[v]=u;
                dep[v]=dep[u]+1;
                int t=dfs(v);
                if(t!=-1){
                    ok=true;
                    if(s!=-1){
                        path.emplace_back(s,t);
                        s=-1;
                    }else s=t;
                }
            }
            if(!ok)s=u;
            return s;
        };
        int root=0;
        for(int i=0;i<n;i++)if(adj[i].size()>1){
            root=i;
            break;
        }
        int s=dfs(root);
        if(s!=-1)path.emplace_back(root,s);
        vector<vector<int>> id(n);
        for(int i=0;i<path.size();i++){
            auto [u,v]=path[i];
            while(u!=v){
                if(dep[u]<dep[v])swap(u,v);
                id[u].emplace_back(i);
                u=par[u];
            }
            id[u].emplace_back(i);
        }
        vector<bool> vis(path.size());
        queue<int> q;
        cout << path.size() << "\n";
        for(int s=0;s<path.size();s++)if(!vis[s]){
            vis[s]=true;
            q.emplace(s);
            while(!q.empty()){
                auto i=q.front();
                q.pop();
                auto [u,v]=path[i];
                cout << u+1 << " " << v+1 << "\n";
                while(u!=v){
                    if(dep[u]<dep[v])swap(u,v);
                    while(!id[u].empty()){
                        int j=id[u].back();
                        id[u].pop_back();
                        if(!vis[j]){
                            vis[j]=true;
                            q.emplace(j);
                        }
                    }
                    u=par[u];
                }
                while(!id[u].empty()){
                    int j=id[u].back();
                    id[u].pop_back();
                    if(!vis[j]){
                        vis[j]=true;
                        q.emplace(j);
                    }
                }
            }
        }
    }
}