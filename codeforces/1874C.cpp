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
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
    }
    vector<vector<db>> dp(n+1,vector<db>(n+5));
    dp[1][1]=1;
    dp[2][1]=0.5;
    for(int i=3;i<=n;i++){
        dp[i][1]=db(1)/i;
        for(int j=2;j<=i;j++){
            dp[i][j]=dp[i-2][j-1]*db(i-j)/i+dp[i-2][j-2]*db(j-2)/i;
        }
    }
    vector<db> dp2(n);
    dp2[n-1]=1;
    for(int i=n-2;i>=0;i--){
        int d=adj[i].size();
        vector<db> a;
        for(auto j:adj[i]){
            a.emplace_back(dp2[j]);
        }
        sort(a.rbegin(),a.rend());
        for(int j=0;j<d;j++){
            dp2[i]+=a[j]*dp[d][j+1];
        }
    }
    cout << dp2[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    while(t--)runcase();
}