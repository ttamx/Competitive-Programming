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
    vector<string> a(2);
    for(auto &x:a){
        cin >> x;
    }
    auto calc=[&](char x,char y,char z){
        return ((x=='A')+(y=='A')+(z=='A'))>=2;
    };
    vector<array<int,2>> dp(n+1,{0,0});
    for(int i=0;i+2<=n;i++){
        if(i%3==0){
            int base=max(dp[i][0],dp[i][1]);
            int cnt=calc(a[0][i],a[0][i+1],a[0][i+2])+calc(a[1][i],a[1][i+1],a[1][i+2]);
            dp[i+3][0]=max(dp[i+3][0],base+cnt);
            dp[i+3][1]=max(dp[i+3][1],base+cnt);
            dp[i+1][0]=max(dp[i+1][0],base+calc(a[0][i],a[1][i],a[0][i+1]));
            dp[i+1][1]=max(dp[i+1][1],base+calc(a[0][i],a[1][i],a[1][i+1]));
        }else if(i%3==1){
            dp[i+1][0]=max(dp[i+1][0],dp[i][1]+calc(a[0][i],a[0][i+1],a[0][i+2]));
            dp[i+1][1]=max(dp[i+1][1],dp[i][0]+calc(a[1][i],a[1][i+1],a[1][i+2]));
            dp[i+2][0]=max(dp[i+2][0],dp[i][0]+calc(a[1][i],a[0][i+1],a[1][i+1]));
            dp[i+2][1]=max(dp[i+2][1],dp[i][1]+calc(a[0][i],a[0][i+1],a[1][i+1]));
        }else{
            dp[i+2][0]=max(dp[i+2][0],dp[i][1]+calc(a[0][i],a[0][i+1],a[0][i+2]));
            dp[i+2][1]=max(dp[i+2][1],dp[i][0]+calc(a[1][i],a[1][i+1],a[1][i+2]));
        }
    }
    cout << max(dp[n][0],dp[n][1]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}