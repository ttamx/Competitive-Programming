#include<bits/stdc++.h>

using namespace std;

#define int long long

using ll = long long;

const ll INF=1e18;

void solve(){
    int n,m,q;
    cin >> n >> m >> q;
    vector<bool> mark(n);
    while(m--){
        int x;
        cin >> x;
        x--;
        mark[x]=true;
    }
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<ll> dp(n),dist(n);
    vector<int> par(n,-1),sz(n),hv(n,-1),hd(n,-1),dep(n),tin(n),tout(n);
    int timer=-1;
    function<void(int)> dfs=[&](int u){
        sz[u]=1;
        for(auto [v,w]:adj[u]){
            if(v==par[u])continue;
            par[v]=u;
            dep[v]=dep[u]+1;
            dist[v]=dist[u]+w;
            if(!mark[v]){
                dp[v]=dp[u]+w;
            }
            dfs(v);
            sz[u]+=sz[v];
            if(hv[u]==-1||sz[v]>sz[hv[u]]){
                hv[u]=v;
            }
        }
    };
    function<void(int)> hld=[&](int u){
        tin[u]=++timer;
        if(hd[u]==-1){
            hd[u]=u;
        }
        if(hv[u]!=-1){
            hd[hv[u]]=hd[u];
            hld(hv[u]);
        }
        for(auto [v,w]:adj[u]){
            if(v==par[u]||v==hv[u])continue;
            hld(v);
        }
        tout[u]=timer;
    };
    dfs(0);
    hld(0);
    auto lca=[&](int u,int v){
        while(hd[u]!=hd[v]){
            if(dep[hd[u]]<dep[hd[v]]){
                swap(u,v);
            }
            u=par[hd[u]];
        }
        return dep[u]<dep[v]?u:v;
    };
    auto in_subtree=[&](int u,int v){
        return tin[u]<=tin[v]&&tout[v]<=tout[u];
    };
    vector<vector<int>> adj2(n);
    vector<ll> dp2(n),dp3(n),max_dist(n),max_cand_dist(n),last_red(n);
    while(q--){
        int k;
        cin >> k;
        vector<int> a(k);
        for(auto &x:a){
            cin >> x;
            x--;
        }
        sort(a.begin(),a.end(),[&](int i,int j){
            return tin[i]<tin[j];
        });
        stack<int> s;
        for(auto x:a){
            int id=-1;
            while(!s.empty()&&!in_subtree(s.top(),x)){
                if(id!=-1){
                    adj2[s.top()].emplace_back(id);
                }
                id=s.top();
                s.pop();
            }
            int u=id==-1?x:lca(id,x);
            if(s.empty()||u!=s.top()){
                s.emplace(u);
            }
            if(id!=-1){
                adj2[u].emplace_back(id);
            }
            if(u!=x){
                s.emplace(x);
            }
        }
        int id=-1;
        while(!s.empty()){
            if(id!=-1){
                adj2[s.top()].emplace_back(id);
            }
            id=s.top();
            s.pop();
        }
        assert(id!=-1);
        vector<int> nodes;
        function<void(int)> dfs2=[&](int u){
            nodes.emplace_back(u);
            dp2[u]=dp[u];
            max_dist[u]=-1;
            max_cand_dist[u]=dist[u];
            last_red[u]=dist[u]-dp[u];
            ll mx=-1,mx2=-1;
            for(auto v:adj2[u]){
                dfs2(v);
                mx2=max(mx2,dp2[v]);
                if(mx2>mx){
                    swap(mx,mx2);
                }
                dp2[u]=max(dp2[u],dp2[v]);
                max_dist[u]=max(max_dist[u],max_dist[v]);
                if(last_red[v]!=last_red[u]){
                    max_dist[u]=max(max_dist[u],max_cand_dist[v]-last_red[v]);
                }else{
                    max_cand_dist[u]=max(max_cand_dist[u],max_cand_dist[v]);
                }
            }
            dp3[u]=min(dp2[u],max(max_dist[u],max_cand_dist[u]-dist[u]));
            for(auto v:adj2[u]){
                dp3[u]=min(dp3[u],max({mx==dp2[v]?mx2:mx,dp[u],dp3[v]}));
            }
        };
        dfs2(id);
        cout << dp3[id] << "\n";
        for(auto x:nodes){
            adj2[x].clear();
        }
    }

}

signed main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}

/*
2
12 2 4
1 9
1 2 1
2 3 4
3 4 3
3 5 2
2 6 2
6 7 1
6 8 2
2 9 5
9 10 2
9 11 3
1 12 10
3 3 7 8
4 4 5 7 8
4 7 8 10 11
3 4 5 12
3 2 3
1 2
1 2 1
1 3 1
1 1
2 1 2
3 1 2 3
*/