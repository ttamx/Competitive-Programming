#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<ll> dp(n),mx(n),mx2(n);
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto [v,w]:adj[u])if(v!=p){
            dfs(v,u);
            mx2[u]=max(mx2[u],dp[v]-w);
            if(mx2[u]>mx[u])swap(mx[u],mx2[u]);
        }
        dp[u]=mx[u]+a[u];
    };
    ll ans=0;
    function<void(int,int,ll)> dfs2=[&](int u,int p,ll up){
        ans=max(ans,dp[u]);
        ans=max(ans,a[u]+up);
        for(auto [v,w]:adj[u])if(v!=p){
            ll val=((dp[v]-w==mx[u])?mx2[u]:mx[u]);
            dfs2(v,u,max(max(val,up)+a[u]-w,0LL));
        }
    };
    dfs(0,-1);
    dfs2(0,-1,0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}