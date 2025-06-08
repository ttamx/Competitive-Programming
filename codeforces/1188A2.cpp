#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    if(n==2){
        int u,v,w;
        cin >> u >> v >> w;
        cout << "YES\n";
        cout << "1\n";
        cout << u << " " << v << " " << w << "\n";
        exit(0);
    }
    vector<vector<pair<int,int>>> adj(n);
    vector<int> w(n-1);
    int root=-1;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v >> w[i];
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    for(int i=0;i<n;i++){
        if(adj[i].size()>1){
            root=i;
        }
        if(adj[i].size()==2){
            cout << "NO\n";
            exit(0);
        }
    }
    assert(root!=-1);
    vector<tuple<int,int,int>> ans;
    vector<int> par(n,-1),pid(n,-1),leaf(n,-1);
    vector<int> ord;
    function<void(int)> dfs=[&](int u){
        ord.emplace_back(u);
        for(auto [v,i]:adj[u])if(v!=par[u]){
            par[v]=u;
            dfs(v);
        }
    };
    dfs(root);
    function<void(int)> dfs2=[&](int u){
        leaf[u]=u;
        for(auto [v,i]:adj[u])if(v!=par[u]){
            par[v]=u;
            pid[v]=i;
            dfs2(v);
            leaf[u]=leaf[v];
        }
    };
    for(auto u:ord){
        if(adj[u].size()==1)continue;
        fill(par.begin(),par.end(),-1);
        dfs2(u);
        for(auto [v,i]:adj[u]){
            if(w[i]==0)continue;
            assert(w[i]%2==0);
            vector<int> a;
            for(auto [x,i]:adj[u])if(x!=v){
                a.emplace_back(leaf[x]);
                if(a.size()==2)break;
            }
            v=leaf[v];
            assert(a.size()==2);
            ans.emplace_back(v,a[0],-w[i]/2);
            ans.emplace_back(v,a[1],-w[i]/2);
            ans.emplace_back(a[0],a[1],w[i]/2);
            while(v!=u){
                w[pid[v]]-=w[i];
                v=par[v];
            }
        }
    }
    assert(w==vector<int>(n-1,0));
    cout << "YES\n";
    cout << ans.size() << "\n";
    for(auto [u,v,w]:ans){
        cout << u+1 << " " << v+1 << " " << -w << "\n";
    }
}