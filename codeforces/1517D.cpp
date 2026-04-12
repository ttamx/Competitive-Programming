#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) a.erase(unique(ALL(a)),a.end())
#define SZ(a) (int)(a.size())
#define LB(a,x) (int)(lower_bound(ALL(a),x)-a.begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-a.begin())
#define MIN(a) *min_element(ALL(a))
#define MAX(a) *max_element(ALL(a))

using ll = long long;
using db = long double;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/4;
const db DINF=numeric_limits<db>::infinity();
const int MOD=998244353;
const int MOD2=1000000007;
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define vv(T,a,n,...) vector<vector<T>> a(n,vector<T>(__VA_ARGS__))
#define vvv(T,a,n,m,...) vector<vector<vector<T>>> a(n,vector<vector<T>>(m,vector<T>(__VA_ARGS__)))
#define vvvv(T,a,n,m,k,...) vector<vector<vector<vector<T>>>> a(n,vector<vector<vector<T>>>(m,vector<vector<T>>(k,vector<T>(__VA_ARGS__))))

template<class T,class U>
bool chmin(T &a,U b){return b<a?a=b,1:0;}
template<class T,class U>
bool chmax(T &a,U b){return a<b?a=b,1:0;}
template<class T,class U>
T SUM(const U &a){return accumulate(ALL(a),T{});}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vv(int,a,n,m-1);
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vv(int,b,n-1,m);
    for(auto &v:b){
        for(auto &x:v){
            cin >> x;
        }
    }
    if(k%2){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                cout << -1 << " \n"[j==m-1];
            }
        }
        return;
    }
    k/=2;
    vvv(int,dp,k+1,n,m,INF);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            dp[0][i][j]=0;
        }
    }
    for(int x=1;x<=k;x++){
        for(int i=0;i<n;i++){
            for(int j=0;j+1<m;j++){
                chmin(dp[x][i][j],dp[x-1][i][j+1]+a[i][j]);
                chmin(dp[x][i][j],dp[x-1][i][j]+a[i][j]);
                chmin(dp[x][i][j+1],dp[x-1][i][j]+a[i][j]);
                chmin(dp[x][i][j+1],dp[x-1][i][j+1]+a[i][j]);
            }
        }
        for(int i=0;i+1<n;i++){
            for(int j=0;j<m;j++){
                chmin(dp[x][i][j],dp[x-1][i+1][j]+b[i][j]);
                chmin(dp[x][i][j],dp[x-1][i][j]+b[i][j]);
                chmin(dp[x][i+1][j],dp[x-1][i][j]+b[i][j]);
                chmin(dp[x][i+1][j],dp[x-1][i+1][j]+b[i][j]);
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cout << dp[k][i][j]*2 << " \n"[j==m-1];
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}