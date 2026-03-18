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
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    vector<vector<int>> pos(n+1);
    for(int i=1;i<=n;i++){
        pos[a[i]].emplace_back(i);
    }
    vector<vector<int>> dp(n+2,vector<int>(n+2));
    for(int l=n;l>=1;l--){
        for(int r=l+1;r<=n;r++){
            dp[l][r]=max(dp[l][r-1],dp[l+1][r]);
            for(auto i:pos[a[l]]){
                if(l<i&&i<=r){
                    dp[l][r]=max(dp[l][r],dp[l][i-1]+dp[i+1][r]+1);
                }
            }
            for(auto i:pos[a[r]]){
                if(l<=i&&i<r){
                    dp[l][r]=max(dp[l][r],dp[l][i-1]+dp[i+1][r]+1);
                }
            }
        }
    }
    cout << n-1-dp[1][n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}