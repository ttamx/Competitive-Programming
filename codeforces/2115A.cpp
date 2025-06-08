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
    int g=0,mx=0;
    for(auto &x:a){
        cin >> x;
        g=gcd(g,x);
        mx=max(mx,x);
    }
    vector<int> dp(mx+1,INF);
    dp[g]=0;
    for(auto x:a){
        for(int j=0;j<=mx;j++){
            dp[j]=min(dp[j],dp[gcd(j,x)]+1);
        }
    }
    int ans=INF;
    for(int i=0;i<n;i++){
        int res=dp[a[i]];
        for(int j=0;j<n;j++){
            if(j!=i&&a[j]!=g){
                res++;
            }
        }
        ans=min(ans,res);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}