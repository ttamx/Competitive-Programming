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
    vector<ll> a(n),b(n),c(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i] >> c[i];
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return b[i]>b[j];
    });
    vector<ll> dp(n+1);
    for(auto i:ord){
        auto ndp=dp;
        for(int j=0;j<=n;j++){
            ndp[j]=max(ndp[j],dp[j]+a[i]-b[i]*c[i]);
        }
        for(int j=1;j<=n;j++){
            ndp[j]=max(ndp[j],dp[j-1]+a[i]-b[i]*(j-1));
        }
        dp=move(ndp);
    }
    cout << *max_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}