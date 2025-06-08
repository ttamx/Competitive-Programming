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
    vector<vector<int>> adj(n);
    vector<ll> c(n),w(n);
    ll C=0;
    for(int i=0;i<n;i++){
        cin >> c[i] >> w[i];
        C=max(C,c[i]);
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
    }
    vector<vector<ll>> dp(n,vector<ll>(C*C+1));
    for(int u=0;u<n;u++){
        for(int i=c[u];i<=C*C;i++){
            dp[u][i]=max(dp[u][i],dp[u][i-c[u]]+w[u]);
        }
        for(auto v:adj[u]){
            for(int i=0;i<=C*C;i++){
                dp[v][i]=max(dp[v][i],dp[u][i]);
            }
        }
    }
    vector<vector<vector<array<ll,2>>>> dp2(n,vector<vector<array<ll,2>>>(n,vector<array<ll,2>>(C,{0,-LINF})));
    for(int x=0;x<n;x++){
        for(int u=0;u<n;u++){
            if(w[u]*c[x]>w[x]*c[u]){
                for(int i=0;i<c[x];i++){
                    for(int f=0;f<2;f++){
                        dp2[x][u][i][f]=-LINF;
                    }
                }
            }
            if(u==x){
                for(int i=0;i<C;i++){
                    dp2[x][u][i][1]=max(dp2[x][u][i][1],dp2[x][u][i][0]);
                }
            }
            int g=gcd(c[u],c[x]);
            for(int s=0;s<g;s++){
                for(int i=s,tt=0;tt<2*c[x];i=(i+c[u])%c[x],tt+=g){
                    for(int f=0;f<2;f++){
                        ll cc=i+c[u],ww=dp2[x][u][i][f]+w[u];
                        ll t=cc/c[x];
                        cc-=t*c[x];
                        ww-=t*w[x];
                        dp2[x][u][cc][f]=max(dp2[x][u][cc][f],ww);
                    }
                }
            }
            for(auto v:adj[u]){
                for(int i=0;i<c[x];i++){
                    for(int f=0;f<2;f++){
                        dp2[x][v][i][f]=max(dp2[x][v][i][f],dp2[x][u][i][f]);
                    }
                }
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        int u,p;
        cin >> u >> p;
        u--;
        if(p<=C*C){
            cout << dp[u][p] << "\n";
        }else{
            ll ans=0;
            for(int i=0;i<n;i++){
                ans=max(ans,dp2[i][u][p%c[i]][1]+(p/c[i])*w[i]);
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