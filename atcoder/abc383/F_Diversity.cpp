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
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<pair<int,int>>> a(n);
    for(int i=0;i<n;i++){
        int x,y,z;
        cin >> x >> y >> z;
        z--;
        a[z].emplace_back(x,y);
    }
    vector<ll> dp(m+1,0);
    for(int i=0;i<n;i++){
        vector<ll> ndp(m+1,0);
        for(auto [p,u]:a[i]){
            for(int j=m;j>=p;j--){
                ndp[j]=max({ndp[j],ndp[j-p]+u,dp[j-p]+u+k});
            }
        }
        for(int i=0;i<=m;i++){
            dp[i]=max(ndp[i],dp[i]);
        }
    }
    cout << dp[m] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}