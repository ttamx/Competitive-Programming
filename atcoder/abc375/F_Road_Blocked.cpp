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
    int n,m,q;
    cin >> n >> m >> q;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    vector<bool> closed(m);
    vector<tuple<int,int,int>> qr(q);
    for(auto &[t,x,y]:qr){
        cin >> t;
        if(t==1){
            cin >> x;
            x--;
            closed[x]=true;
        }else{
            cin >> x >> y;
            x--,y--;
        }
    }
    reverse(qr.begin(),qr.end());
    vector<vector<ll>> dp(n,vector<ll>(n,LINF));
    for(int i=0;i<n;i++){
        dp[i][i]=0;
    }
    for(int i=0;i<m;i++){
        if(!closed[i]){
            auto [u,v,w]=edges[i];
            dp[u][v]=min(dp[u][v],(ll)w);
            dp[v][u]=min(dp[v][u],(ll)w);
        }
    }
    for(int x=0;x<n;x++){
        for(int u=0;u<n;u++){
            for(int v=0;v<n;v++){
                dp[u][v]=min(dp[u][v],dp[u][x]+dp[x][v]);
            }
        }
    }
    vector<ll> ans;
    for(auto [t,x,y]:qr){
        if(t==1){
            auto [u,v,w]=edges[x];
            for(int i=0;i<n;i++){
                for(int j=0;j<n;j++){
                    dp[i][j]=min(dp[i][j],dp[i][u]+w+dp[v][j]);
                    dp[i][j]=min(dp[i][j],dp[i][v]+w+dp[u][j]);
                }
            }
        }else{
            ans.emplace_back(dp[x][y]);
        }
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << (x<LINF?x:-1) << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}