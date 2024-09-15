#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/2;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<tuple<int,int,int>> edges(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    vector<tuple<int,int,int>> cands;
    sort(edges.begin(),edges.end());
    int cnt=0;
    ll cost=0;
    for(auto [w,u,v]:edges){
        int fu=fp(u),fv=fp(v);
        if(fu!=fv){
            fa[fv]=fu;
            adj[u].emplace_back(v,w);
            adj[v].emplace_back(u,w);
            cnt++;
            cost+=w;
        }else{
            cands.emplace_back(u,v,w);
        }
    }
    if(cnt<n-1){
        cout << -1 << " " << -1 << "\n";
        return;
    }
    int lg=1;
    while((1<<lg)<=n){
        lg++;
    }
    vector<int> dep(n);
    vector<vector<int>> pa(lg,vector<int>(n));
    vector<vector<array<ll,2>>> mx(lg,vector<array<ll,2>>(n,{-LINF,-LINF}));
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto [v,w]:adj[u]){
            if(v==p){
                continue;
            }
            dep[v]=dep[u]+1;
            pa[0][v]=u;
            mx[0][v][w&1]=w;
            for(int i=1;i<lg;i++){
                int x=pa[i-1][v];
                pa[i][v]=pa[i-1][x];
                mx[i][v][0]=max(mx[i-1][v][0],mx[i-1][x][0]);
                mx[i][v][1]=max(mx[i-1][v][1],mx[i-1][x][1]);
            }
            dfs(v,u);
        }
    };
    dfs(0,-1);
    ll cost2=LINF;
    for(auto [u,v,w]:cands){
        if(dep[u]<dep[v]){
            swap(u,v);
        }
        ll res=-LINF;
        for(int i=lg-1;i>=0;i--){
            int x=pa[i][u];
            if(dep[x]>=dep[v]){
                res=max(res,mx[i][u][w&1^1]);
                u=x;
            }
        }
        if(u!=v){
            for(int i=lg-1;i>=0;i--){
                int x=pa[i][u],y=pa[i][v];
                if(x!=y){
                    res=max(res,mx[i][u][w&1^1]);
                    res=max(res,mx[i][v][w&1^1]);
                    u=x,v=y;
                }
            }
            res=max(res,mx[0][u][w&1^1]);
            res=max(res,mx[0][v][w&1^1]);
            u=pa[0][u];
            v=pa[0][v];
        }
        assert(u==v);
        if(res>-LINF){
            cost2=min(cost2,cost+w-res);
        }
    }
    if(cost&1){
        swap(cost,cost2);
    }
    cout << (cost<LINF?cost:-1LL) << " " << (cost2<LINF?cost2:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}