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
    for(auto &[w,u,v]:e){
        cin >> u >> v >> w;
        u--,v--;
    }
    sort(e.begin(),e.end());
    vector<vector<int>> dp(n,vector<int>(n,n+1));
    vector<vector<vector<int>>> mem;
    vector<int> ans;
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
        if(dp[u][v]==0)continue;
        for(int s=0;s<n;s++){
            for(int t=0;t<n;t++){
                dp[s][t]=min({dp[s][t],dp[s][u]+dp[v][t],dp[s][v]+dp[u][t]});
            }
        }
        mem.emplace_back(dp);
        ans.emplace_back(w);
    }
    while(q--){
        int u,v,k;
        cin >> u >> v >> k;
        u--,v--;
        int l=0,r=ans.size()-1;
        while(l<r){
            int m=(l+r)/2;
            if(mem[m][u][v]<k)r=m;
            else l=m+1;
        }
        cout << ans[l] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}