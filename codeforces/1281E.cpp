#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

void runcase(){
    int n;
    cin >> n;
    n*=2;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<int> sz(n);
    function<ll(int,int)> dfs=[&](int u,int p)->ll {
        ll res=0;
        sz[u]=1;
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            res+=dfs(v,u);
            if(sz[v]&1)res+=w;
            sz[u]+=sz[v];
        }
        return res;
    };
    ll ans1=dfs(0,-1);
    ll ans2=0;
    function<int(int,int)> centroid=[&](int u,int p){
        for(auto [v,w]:adj[u])if(v!=p&&sz[v]*2>n)return centroid(v,u);
        return u;
    };
    function<int(int,int)> dfs2=[&](int u,int p)->int {
        int s=1;
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            int t=dfs2(v,u);
            ans2+=1LL*w*t;
            s+=t;
        }
        return s;
    };
    dfs2(centroid(0,-1),-1);
    cout << ans1 << " " << ans2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}