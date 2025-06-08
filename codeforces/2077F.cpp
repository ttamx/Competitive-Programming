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
    int n,m;
    cin >> n >> m;
    int s=1;
    while(s<=m)s<<=1;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    ll ans=0;
    for(int i=0;i<n;i++)ans+=abs(a[i]-b[i]);
    using P = pair<ll,int>;
    using T = array<P,2>;
    auto upd=[&](T &x,P v){
        if(x[0].second==v.second)x[0]=min(x[0],v);
        else x[1]=min(x[1],v);
        if(x[1]<x[0])swap(x[0],x[1]);
    };
    vector<T> dp(s,T{P{LINF,-1},P{LINF,-2}});
    for(int i=0;i<n;i++){
        upd(dp[b[i]],{0,i});
    }
    for(int i=1;i<s;i++){
        for(int j=0;j<2;j++){
            upd(dp[i],{dp[i-1][j].first+1,dp[i-1][j].second});
        }
    }
    auto dp2=dp;
    for(int i=0;i<s;i++){
        for(int j=1;j<s;j<<=1){
            if(i&j){
                for(int k=0;k<2;k++){
                    upd(dp[i],dp[i^j][k]);
                }
            }
        }
        for(auto [u,ui]:dp[i]){
            for(auto [v,vi]:dp2[i]){
                if(ui!=vi){
                    ans=min(ans,u+v);
                }
            }
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