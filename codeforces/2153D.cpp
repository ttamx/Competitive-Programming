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
    auto cost2=[&](int i,int j){
        return abs(a[i]-a[j]);
    };
    auto cost3=[&](int i,int j,int k){
        return max({a[i],a[j],a[k]})-min({a[i],a[j],a[k]});
    };
    auto solve=[&](int l,int r){
        array<ll,3> dp{0LL,LINF,LINF};
        for(int i=l;i<=r;i++){
            ll cur=LINF;
            if(i>l){
                cur=min(cur,dp[1]+cost2(i,i-1));
            }
            if(i>l+1){
                cur=min(cur,dp[2]+cost3(i,i-1,i-2));
            }
            dp={cur,dp[0],dp[1]};
        }
        return dp[0];
    };
    ll ans=solve(0,n-1);
    ans=min(ans,solve(1,n-2)+cost2(0,n-1));
    ans=min(ans,solve(1,n-3)+cost3(0,n-1,n-2));
    ans=min(ans,solve(2,n-2)+cost3(0,1,n-1));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}