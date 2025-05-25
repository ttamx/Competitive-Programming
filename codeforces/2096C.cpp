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
    vector<vector<ll>> h(n,vector<ll>(n));
    for(auto &v:h)for(auto &x:v)cin >> x;
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    ll ans=0;
    {
        vector<array<ll,2>> dp(n,{LINF,LINF});
        dp[0][0]=0;
        dp[0][1]=a[0];
        for(int i=0;i+1<n;i++){
            array<array<bool,2>,2> f;
            f[0][0]=f[0][1]=f[1][0]=f[1][1]=false;
            for(int j=0;j<n;j++){
                for(int x=0;x<2;x++){
                    for(int y=0;y<2;y++){
                        if(h[i][j]+x==h[i+1][j]+y){
                            f[x][y]=true;
                        }
                    }
                }
            }
            for(int x=0;x<2;x++){
                for(int y=0;y<2;y++){
                    if(f[x][y])continue;
                    dp[i+1][y]=min(dp[i+1][y],dp[i][x]+y*a[i+1]);
                }
            }
        }
        ll res=min(dp[n-1][0],dp[n-1][1]);
        if(res>=LINF)return void(cout << -1 << "\n");
        ans+=res;
    }
    {
        vector<array<ll,2>> dp(n,{LINF,LINF});
        dp[0][0]=0;
        dp[0][1]=b[0];
        for(int i=0;i+1<n;i++){
            array<array<bool,2>,2> f;
            f[0][0]=f[0][1]=f[1][0]=f[1][1]=false;
            for(int j=0;j<n;j++){
                for(int x=0;x<2;x++){
                    for(int y=0;y<2;y++){
                        if(h[j][i]+x==h[j][i+1]+y){
                            f[x][y]=true;
                        }
                    }
                }
            }
            for(int x=0;x<2;x++){
                for(int y=0;y<2;y++){
                    if(f[x][y])continue;
                    dp[i+1][y]=min(dp[i+1][y],dp[i][x]+y*b[i+1]);
                }
            }
        }
        ll res=min(dp[n-1][0],dp[n-1][1]);
        if(res>=LINF)return void(cout << -1 << "\n");
        ans+=res;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}