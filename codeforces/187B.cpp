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

const int N=65;
const int T=1005;
const int Q=1e5+5;

int n,m,q;
int dist[N][N],dp[N][N][N],dp2[N][N],memo[N][N];
vector<tuple<int,int,int>> qr[T];
int ans[Q];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++){
        for(int u=1;u<=n;u++){
            for(int v=1;v<=n;v++){
                cin >> dp[i][u][v];
            }
        }
        for(int x=1;x<=n;x++){
            for(int u=1;u<=n;u++){
                for(int v=1;v<=n;v++){
                    dp[i][u][v]=min(dp[i][u][v],dp[i][u][x]+dp[i][x][v]);
                }
            }
        }
    }
    for(int i=1;i<=q;i++){
        int s,t,k;
        cin >> s >> t >> k;
        qr[k+1].emplace_back(s,t,i);
    }
    for(int u=1;u<=n;u++){
        for(int v=1;v<=n;v++){
            dist[u][v]=INF;
        }
    }
    for(int u=1;u<=n;u++){
        for(int v=1;v<=n;v++){
            if(u!=v)dp2[u][v]=INF;
        }
    }
    for(int i=1;i<=m;i++){
        for(int u=1;u<=n;u++){
            for(int v=1;v<=n;v++){
                dist[u][v]=min(dist[u][v],dp[i][u][v]);
            }
        }
    }
    for(int t=1;t<T;t++){
        for(int u=1;u<=n;u++){
            for(int v=1;v<=n;v++){
                memo[u][v]=dp2[u][v];
            }
        }
        for(int u=1;u<=n;u++){
            for(int v=1;v<=n;v++){
                for(int x=1;x<=n;x++){
                    dp2[u][v]=min(dp2[u][v],memo[u][x]+dist[x][v]);
                }
            }
        }
        for(auto [s,e,i]:qr[t]){
            ans[i]=dp2[s][e];
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}