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
    if(n==1){
        cout << 0 << "\n";
        return; // how did i forgot this...
    }
    vector<ll> b(n,LINF);
    for(int i=0;i<n;i++){
        if(i>0)b[i]=min(b[i],a[i]-a[i-1]);
        if(i+1<n)b[i]=min(b[i],a[i+1]-a[i]);
    }
    vector<ll> dp(n),l(n),r(n);
    ll ans=1;
    dp[0]=0,l[0]=0,r[0]=b[0];
    dp[1]=1,l[1]=0,r[1]=b[1];
    for(int i=2;i<n;i++){
        dp[i]=dp[i-2]+1;
        l[i]=0,r[i]=b[i];
        ll cl=max(0LL,l[i-2]+a[i-2]+a[i]-2*a[i-1]);
        ll cr=min(b[i],r[i-2]+a[i-2]+a[i]-2*a[i-1]);
        if(cl<cr){
            dp[i]++;
            l[i]=cl;
            r[i]=cr;
        }
        ans=max(ans,dp[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}