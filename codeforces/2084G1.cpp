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
    ll n;
    cin >> n;
    vector<int> a(n),t(n+1,-1);
    for(int i=0;i<n;i++){
        cin >> a[i];
        if(a[i])t[a[i]]=i%2;
    }
    if(n==1){
        cout << 1 << "\n";
        return;
    }
    ll h=(n+1)/2;
    vector<ll> dp(n+5,-LINF);
    dp[0]=0;
    for(ll i=1;i<=n;i++){
        vector<ll> ndp(n+5,-LINF);
        if(t[i]==-1||t[i]==0){
            for(ll j=0;j<=n;j++){
                ndp[j+1]=max(ndp[j+1],dp[j]+i*j+i*(n-h-(i-1-j)));
            }
        }
        if(t[i]==-1||t[i]==1){
            for(ll j=0;j<=n;j++){
                ndp[j]=max(ndp[j],dp[j]+i*(i-1-j)+i*(h-j));
            }
        }
        dp=move(ndp);
    }
    cout << dp[h]+1LL*n*(n+1)/2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}