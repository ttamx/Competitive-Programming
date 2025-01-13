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
    vector<tuple<int,int,int>> e(m);
    vector<tuple<int,int,int>> qr(q);
    for(auto &[w,u,v]:e){
        cin >> u >> v >> w;
        u--,v--;
    }
    for(auto &[u,v,k]:qr){
        cin >> u >> v >> k;
        u--,v--;
    }
    sort(e.begin(),e.end());
    vector<int> l(q),r(q,m-1);
    vector<vector<int>> event(m);
    while(true){
        bool done=true;
        for(int i=0;i<q;i++){
            if(l[i]<r[i]){
                event[(l[i]+r[i])/2].emplace_back(i);
                done=false;
            }
        }
        if(done)break;
        vector<vector<int>> dp(n,vector<int>(n,n+1));
        for(int i=0;i<n;i++)dp[i][i]=0;
        for(auto [w,v,u]:e){
            dp[u][v]=dp[v][u]=1;
        }
        for(int x=0;x<n;x++){
            for(int u=0;u<n;u++){
                for(int v=0;v<n;v++){
                    dp[u][v]=min(dp[u][v],dp[u][x]+dp[x][v]);
                }
            }
        }
        for(int i=0;i<m;i++){
            auto [w,u,v]=e[i];
            for(int s=0;s<n;s++){
                for(int t=0;t<n;t++){
                    dp[s][t]=min({dp[s][t],dp[s][u]+dp[v][t],dp[s][v]+dp[u][t]});
                }
            }
            for(auto j:event[i]){
                auto [uu,vv,k]=qr[j];
                if(dp[uu][vv]<k)r[j]=i;
                else l[j]=i+1;
            }
            event[i].clear();
        }
    }
    for(auto x:l){
        cout << get<0>(e[x]) << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}