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
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<vector<array<ll,2>>> dp(n,vector<array<ll,2>>(k+1,{-LINF,-LINF}));
    function<void(int,int)> dfs=[&](int u,int p){
        vector<array<ll,3>> aux(k+2,{0LL,-LINF,-LINF});
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            vector<array<ll,3>> new_aux(k+2,{0LL,-LINF,-LINF});
            for(int i=0;i<=k;i++){
                for(int j=0;i+j<=k+1;j++){
                    for(int x=0;x<2;x++){
                        for(int y=0;x+y<3;y++){
                            new_aux[i+j][x+y]=max(new_aux[i+j][x+y],dp[v][i][x]+aux[j][y]);
                        }
                    }
                }
            }
            aux=move(new_aux);
        }
        dp[u][0][0]=0;
        for(int i=1;i<=k;i++){
            dp[u][i][1]=max(aux[i-1][0],aux[i][1])+a[u];
            dp[u][i][0]=max({dp[u][i][1],aux[i][0],aux[i+1][2]+a[u]});
        }
    };
    dfs(0,-1);
    ll ans=0;
    cout << dp[0][k][0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}