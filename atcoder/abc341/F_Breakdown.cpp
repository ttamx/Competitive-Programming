#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pii> ed(m);
    for(auto &[u,v]:ed)cin >> u >> v,u--,v--;
    vector<vi> adj(n);
    vl w(n),a(n);
    for(auto &x:w)cin >> x;
    for(auto &x:a)cin >> x;
    for(auto [u,v]:ed){
        if(w[u]==w[v])continue;
        if(w[u]<w[v])swap(u,v);
        adj[u].emplace_back(v);
    }
    vi id(n);
    iota(all(id),0);
    sort(all(id),[&](int i,int j){
        return w[i]<w[j];
    });
    ll ans=0;
    vl dp(n);
    for(auto u:id){
        vl dp2(w[u]);
        for(auto v:adj[u]){
            for(int i=w[u]-1;i>=w[v];i--)dp2[i]=max(dp2[i],dp2[i-w[v]]+dp[v]);
        }
        dp[u]=dp2[w[u]-1]+1;
        ans+=a[u]*dp[u];
    }
    cout << ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    // cin >> t;
    while(t--)runcase();
}