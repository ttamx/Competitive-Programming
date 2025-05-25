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
    vector<ll> a(n),b(n);
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y;
        a[i]=x+y;
        b[i]=x-y;
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return b[i]<b[j];
    });
    vector<array<ll,3>> dp(n+1,{LINF,LINF,LINF});
    vector<ll> ans(n+1,LINF);
    for(int ii=0;ii<n;ii++){
        int i=ord[ii];
        auto ndp=dp;
        ndp[1][0]=min(ndp[1][0],a[i]*2-b[i]*2);
        ndp[1][1]=min(ndp[1][1],a[i]-b[i]);
        for(int j=1;j<=n;j++){
            for(int k=0;k<3;k++){
                ndp[j][k]=min(ndp[j][k],dp[j-1][k]+a[i]*2);
            }
            ndp[j][1]=min(ndp[j][1],dp[j-1][0]+a[i]+b[i]);
            ndp[j][2]=min(ndp[j][2],dp[j-1][1]+a[i]-b[i]);
        }
        dp=move(ndp);
        for(int j=2;j<=n;j++){
            ans[j]=min(ans[j],dp[j][2]+b[i]*2);
        }
    }
    for(int i=2;i<=n;i++){
        cout << ans[i]/2 << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}