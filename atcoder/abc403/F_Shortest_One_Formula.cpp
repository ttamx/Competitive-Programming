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

const int N=2005;

int dp[N][2];
tuple<int,int,int> par[N][2];

int calc_dp(int n,int s){
    if(dp[n][s])return dp[n][s];
    dp[n][s]=INF;
    for(int i=1;i<n;i++){
        int l=calc_dp(i,0);
        int r=calc_dp(n-i,0);
        int res=l+r+1;
        if(s)res+=2;
        if(res<dp[n][s]){
            dp[n][s]=res;
            par[n][s]={i,n-i,0};
        }
    }
    for(int i=2;i*i<=n;i++){
        if(n%i)continue;
        int l=calc_dp(i,1);
        int r=calc_dp(n/i,1);
        int res=l+r+1;
        if(res<dp[n][s]){
            dp[n][s]=res;
            par[n][s]={i,n/i,1};
        }
    }
    return dp[n][s];
}

string get_ans(int n,int s){
    if(n==1)return "1";
    if(n==11)return "11";
    if(n==111)return "111";
    if(n==1111)return "1111";
    auto [l,r,o]=par[n][s];
    string res=get_ans(l,o)+(o?"*":"+")+get_ans(r,o);
    if(o==0&&s==1)res="("+res+")";
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[1][0]=dp[1][1]=1;
    dp[11][0]=dp[11][1]=2;
    dp[111][0]=dp[111][1]=3;
    dp[1111][0]=dp[1111][1]=4;
    int n;
    cin >> n;
    calc_dp(n,0);
    cout << get_ans(n,0) << "\n";
}