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
    int k;
    cin >> k;
    string s,t;
    cin >> s >> t;
    int n=s.size(),m=t.size();
    if(abs(n-m)>k){
        cout << "No\n";
        return;
    }
    s=" "+s;
    t=" "+t;
    vector<vector<int>> dp(n+1,vector<int>(k*2+1,INF));
    for(int i=0;i<=min(k,m);i++){
        dp[0][i+k]=i;
    }
    for(int i=0;i<=min(k,n);i++){
        dp[i][k-i]=i;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<=2*k;j++){
            int p=i+j-k;
            if(p<1||p>m)continue;
            if(j-1>=0)dp[i][j]=min(dp[i][j],dp[i][j-1]+1);
            if(j+1<=2*k)dp[i][j]=min(dp[i][j],dp[i-1][j+1]+1);
            dp[i][j]=min(dp[i][j],dp[i-1][j]+(s[i]!=t[p]));
        }
    }
    cout << (dp[n][m-n+k]<=k?"Yes":"No") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}