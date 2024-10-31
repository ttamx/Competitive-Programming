#include "OES.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int MOD=1e9+7;

int n;
vector<pair<int,int>> adj[N];
ll dp[N][2],dp2[N][2],cnt[N][2];
ll ans;

void dfs(int u,int p){
    if(adj[u].size()==1){
        cnt[u][0]=1;
    }
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        int b=w&1;
        for(int i=0;i<2;i++){
            dp2[v][i]=(dp2[v][i]+cnt[v][i]*w%MOD*w)%MOD;
            dp2[v][i]=(dp2[v][i]+dp[v][i]*w*2)%MOD;
            dp[v][i]=(dp[v][i]+cnt[v][i]*w)%MOD;
        }
        if(w&1){
            swap(dp[v][0],dp[v][1]);
            swap(dp2[v][0],dp2[v][1]);
            swap(cnt[v][0],cnt[v][1]);
        }
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                ll val=(dp2[u][i]*cnt[v][j]+dp2[v][j]*cnt[u][i])%MOD;;
                val=(val+dp[u][i]*dp[v][j]*2)%MOD;
                ans+=(i^j)?MOD-val:val;
                ans%=MOD;
            }
        }
        for(int i=0;i<2;i++){
            dp[u][i]=(dp[u][i]+dp[v][i])%MOD;
            dp2[u][i]=(dp2[u][i]+dp2[v][i])%MOD;
            cnt[u][i]=(cnt[u][i]+cnt[v][i])%MOD;
        }
    }
}

int machinepower(int _n,vector<int> _u,vector<int> _v,vector<int> _w){
    n=_n;
    if(n==2){
        int res=1LL*_w[0]*_w[0]%MOD;
        return _w[0]%2==0?res:(MOD-res)%MOD;
    }
    for(int i=0;i<n-1;i++){
        int u=_u[i],v=_v[i],w=_w[i];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=0;i<n;i++){
        if(adj[i].size()>1){
            dfs(i,-1);
            return ans;
        }
    }
    assert(false);
    return -1;
}