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
    string a,b,c;
    cin >> a >> b >> c;
    int n=a.size();
    int m=b.size();
    int k=c.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,INF));
    dp[0][0]=0;
    for(int i=1;i<=k;i++){
        for(int x=0;x<=min(n,i);x++){
            int y=i-x;
            if(y>m)continue;
            if(x>=1){
                dp[x][y]=min(dp[x][y],dp[x-1][y]+(a[x-1]!=c[i-1]));
            }
            if(y>=1){
                dp[x][y]=min(dp[x][y],dp[x][y-1]+(b[y-1]!=c[i-1]));
            }
        }
    }
    cout << dp[n][m] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}