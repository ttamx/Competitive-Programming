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
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    a.insert(a.end(),a.begin(),a.end());
    vector<vector<ll>> dp(2*n,vector<ll>(2*n));
    ll ans=0;
    for(int s=2;s<n;s++){
        for(int l=0,r=s;r<2*n;l++,r++){
            for(int m=l;m<r;m++){
                dp[l][r]=max(dp[l][r],dp[l][m]+dp[m+1][r]);
            }
            for(int m=l+1;m<r;m++){
                dp[l][r]=max(dp[l][r],dp[l+1][m-1]+dp[m+1][r-1]+a[l]*a[m]*a[r]);
            }
            ans=max(ans,dp[l][r]);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}