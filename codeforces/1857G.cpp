#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=998244353;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res*=a,res%=mod;
        a*=a;
        a%=mod;
        b>>=1;
    }
    return res;
}

void runcase(){
    int n;
    ll s;
    cin >> n >> s;
    vector<tuple<ll,int,int>> a(n-1);
    for(auto &[w,u,v]:a)cin >> u >> v >> w,u--,v--;
    sort(a.begin(),a.end());
    vector<int> p(n),sz(n,1);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        if(p[u]==u)return u;
        return p[u]=fp(p[u]);
    };
    ll ans=1;
    for(auto [w,u,v]:a){
        u=fp(u),v=fp(v);
        ans*=binpow(s-w+1,1ll*sz[u]*sz[v]-1);
        ans%=mod;
        sz[u]+=sz[v];
        p[v]=u;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}