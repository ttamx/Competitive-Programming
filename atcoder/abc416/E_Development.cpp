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
    vector<vector<ll>> dp(n+1,vector<ll>(n+1,LINF));
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        dp[u][v]=min(dp[u][v],(ll)w);
        dp[v][u]=min(dp[v][u],(ll)w);
    }
    int k,t;
    cin >> k >> t;
    for(int i=0;i<k;i++){
        int u;
        cin >> u;
        dp[u][0]=0;
        dp[0][u]=t;
    }
    for(int i=0;i<=n;i++)dp[i][i]=0;
    for(int x=0;x<=n;x++){
        for(int u=0;u<=n;u++){
            for(int v=0;v<=n;v++){
                dp[u][v]=min(dp[u][v],dp[u][x]+dp[x][v]);
            }
        }
    }
    auto add_edge=[&](int u,int v,int w){
        for(int uu=0;uu<=n;uu++){
            for(int vv=0;vv<=n;vv++){
                dp[uu][vv]=min(dp[uu][vv],dp[uu][u]+dp[v][vv]+w);
            }
        }
    };
    int q;
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int u,v,w;
            cin >> u >> v >> w;
            add_edge(u,v,w);
            add_edge(v,u,w);
        }else if(op==2){
            int u;
            cin >> u;
            add_edge(u,0,0);
            add_edge(0,u,t);
        }else{
            ll ans=0;
            for(int u=1;u<=n;u++){
                for(int v=1;v<=n;v++){
                    if(dp[u][v]<LINF){
                        ans+=dp[u][v];
                    }
                }
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