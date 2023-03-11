#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll mod=1e9+7;

int n;
ll dp[N],ch[N];
ll fac[N],inv[N];
vector<int> adj[N];

ll binpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res*=a,res%=mod;
        a*=a,a%=mod;
        b/=2;
    }
    return res;
}

ll C(int n,int r){
    return (((fac[n]*inv[n-r])%mod)*inv[r])%mod;
}

void dfs(int u,int p){
    ch[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        ch[u]+=ch[v];
    }
}

void dfs2(int u,int p){
    int cnt=ch[u]-1;
    dp[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs2(v,u);
        dp[u]*=C(cnt,ch[v]),dp[u]%=mod;
        dp[u]*=dp[v],dp[u]%=mod;
        cnt-=ch[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=(fac[i-1]*i)%mod;
        inv[i]=binpow(fac[i],mod-2);
    }
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,0);
    cout << dp[1];
}