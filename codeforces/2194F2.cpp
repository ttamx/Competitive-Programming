#pragma GCC optimize("O3,unroll-loops")
#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

const int N=1e5+5;
const int K=10;

int n,k,kk;
int a[N],b[K];
int val[1<<K];
int sum[N];
mint dp[N][1<<K];
basic_string<int> adj[N];
mint inv;

inline void fwht(mint *a){
    for(int i=1;i<kk;i<<=1){
        for(int j=0;j<kk;j++){
            if(j&i){
                mint &u=a[j^i],&v=a[j];
                tie(u,v)=make_pair(u+v,u-v);
            }
        }
    }
}

void dfs(int u,int p){
    sum[u]=a[u];
    dp[u][0]=1;
    fwht(dp[u]);
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        sum[u]^=sum[v];
        fwht(dp[v]);
        for(int i=0;i<kk;i++)dp[u][i]*=dp[v][i];
    }
    fwht(dp[u]);
    for(int i=0;i<kk;i++)dp[u][i]*=inv;
    if(u==0)return;
    vector<pair<int,mint>> upd;
    for(int mask=0;mask<kk;mask++){
        int cur=sum[u]^val[mask];
        for(int i=0;i<k;i++){
            if(cur==b[i]){
                upd.emplace_back(mask^(1<<i),dp[u][mask]);
            }
        }
    }
    for(auto [i,v]:upd)dp[u][i]+=v;
}

void runcase(){
    cin >> n >> k;
    kk=1<<k;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u]+=v;
        adj[v]+=u;
    }
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=0;i<k;i++)cin >> b[i];
    for(int mask=0;mask<1<<k;mask++){
        for(int i=0;i<k;i++){
            if(mask>>i&1){
                val[mask]^=b[i];
            }
        }
    }
    inv=mint(kk).inv();
    dfs(0,-1);
    mint ans=0;
    for(int mask=0;mask<kk;mask++){
        int cur=sum[0]^val[mask];
        for(int i=0;i<k;i++){
            if(cur==b[i]){
                ans+=dp[0][mask];
            }
        }
    }
    cout << ans << "\n";
    for(int i=0;i<n;i++)adj[i].clear();
    for(int i=0;i<n;i++)for(int j=0;j<kk;j++)dp[i][j]=0;
    for(int i=0;i<kk;i++)val[i]=0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}