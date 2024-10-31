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
    n++,m++;
    int k;
    cin >> k;
    vector<tuple<int,int,int>> a(k);
    for(auto &[t,d,x]:a){
        cin >> t >> d >> x;
    }
    sort(a.begin(),a.end());
    vector<vector<int>> dp(n,vector<int>(m,INF));
    dp[0][0]=0;
    auto bfs=[&](){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(i+1<n){
                    dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
                }
                if(j+1<m){
                    dp[i][j+1]=min(dp[i][j+1],dp[i][j]+1);
                }
            }
        }
    };
    int pt=0;
    for(auto [t,d,x]:a){
        if(t!=pt){
            bfs();
            for(auto &v:dp){
                for(auto &x:v){
                    if(x>t){
                        x=INF;
                    }
                }
            }
            if(dp[n-1][m-1]<t){
                cout << dp[n-1][m-1] << "\n";
                return;
            }
        }
        if(d==1){
            for(int i=0;i<m;i++){
                dp[x][i]=INF;
            }
        }else{
            for(int i=0;i<n;i++){
                dp[i][x]=INF;
            }
        }
        for(auto &v:dp){
            for(auto &x:v){
                if(x<t){
                    x=t;
                }
            }
        }
    }
    bfs();
    cout << (dp[n-1][m-1]<INF?dp[n-1][m-1]:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}