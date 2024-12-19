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
    vector<int> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    int s=1;
    while(s*s<n)s++;
    vector<vector<int>> dp(s+1,vector<int>(n+1));
    for(int i=0;i<=s;i++){
        for(int j=n;j>=1;j--){
            dp[i][j]=1;
            int v=j+a[j]+i;
            if(v<=n)dp[i][j]+=dp[i][v];
        }
    }
    int q;
    cin >> q;
    while(q--){
        int p,k;
        cin >> p >> k;
        if(k<=s){
            cout << dp[k][p] << "\n";
        }else{
            int ans=0;
            while(p<=n){
                p+=a[p]+k;
                ans++;
            }
            cout << ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}