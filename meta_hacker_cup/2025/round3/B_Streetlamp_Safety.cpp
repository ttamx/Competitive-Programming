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
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    for(int i=1;i<n;i++){
        b[i]=max(b[i],b[i-1]);
    }
    for(int i=n-2;i>=0;i--){
        b[i]=max(b[i],b[i+1]-1);
    }
    int m=b[n-1];
    vector<int> pos(m+1);
    for(int i=0;i<n;i++){
        pos[b[i]]=i;
    }
    vector<ll> f(n+1);
    for(int i=0;i<n;i++){
        f[i+1]=f[i]+a[i];
    }
    vector<ll> dp(m+1,LINF),dp2(m+1,LINF);
    dp[0]=dp2[0]=0;
    vector<vector<pair<int,ll>>> upd(n+1);
    for(int i=0;i<n;i++){
        for(int j=m;j>=1;j--){
            dp[j]=dp[j-1]+a[i];
        }
        dp[0]=0LL;
        for(auto [j,v]:upd[i]){
            dp[j]=min(dp[j],v);
        }
        for(int j=0;j<=m;j++){
            dp2[j]=min(dp2[j],dp[j]);
        }
        for(int j=0;j<b[i];j++){
            dp[j]=dp2[j]=LINF;
        }
        for(int j=0;j<m;j++){
            if(i+j<=pos[j+1]){
                upd[i+j].emplace_back(j,dp2[j]+f[i+j+1]-f[i]);
            }
        }
    }
    cout << dp2[m] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cerr << "Case #" << i << endl;
        cout << "Case #" << i << ": ";
        runcase();
    }
}