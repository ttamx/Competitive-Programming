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
const int MOD=1000000007;
// const int MOD=998244353;
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

const int N=1e5+5;

int dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q,k;
    cin >> q >> k;
    dp[0]=1;
    for(int i=1;i<N;i++){
        dp[i]=dp[i-1];
        if(i>=k){
            dp[i]+=dp[i-k];
            if(dp[i]>=MOD)dp[i]-=MOD;
        }
    }
    for(int i=1;i<N;i++){
        dp[i]+=dp[i-1];
        if(dp[i]>=MOD)dp[i]-=MOD;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        int ans=dp[r]-dp[l-1];
        if(ans<0)ans+=MOD;
        cout << ans << "\n";
    }
}