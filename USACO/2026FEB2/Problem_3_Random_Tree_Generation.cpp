#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1e9+7;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

void runcase(){
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
    vector<int> sz(n);
    function<void(int,int)> dfs=[&](int u,int p){
        sz[u]=1;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            sz[u]+=sz[v];
        }
    };
    dfs(0,-1);
    ll base=1;
    for(int i=1;i<n;i++)base=base*sz[i]%MOD;
    ll ans=0;
    function<void(int,int)> dfs2=[&](int u,int p){
        ans=(ans+binpow(base,MOD-2))%MOD;
        for(auto v:adj[u])if(v!=p){
            ll tmp=base;
            base=base*(n-sz[v])%MOD*binpow(sz[v],MOD-2)%MOD;
            dfs2(v,u);
            base=tmp;
        }
    };
    dfs2(0,-1);
    ll fac=1;
    for(int i=1;i<=n;i++)fac=fac*i%MOD;
    cout << ans*binpow(fac,MOD-2)%MOD << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}