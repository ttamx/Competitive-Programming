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
    int n,k;
    cin >> n >> k;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<array<ll,2>> dp(n,array<ll,2>{});
    function<void(int,int)> dfs=[&](int u,int p){
        ll sum=0;
        vector<ll> a;
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            sum+=dp[v][0];
            a.emplace_back(max(dp[v][1]+w-dp[v][0],0LL));
        }
        sort(a.rbegin(),a.rend());
        dp[u][0]=dp[u][1]=sum;
        for(int i=0;i<min((int)a.size(),k);i++)dp[u][0]+=a[i];
        for(int i=0;i<min((int)a.size(),k-1);i++)dp[u][1]+=a[i];
    };
    dfs(0,-1);
    cout << max(dp[0][0],dp[0][1]) <<"\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}