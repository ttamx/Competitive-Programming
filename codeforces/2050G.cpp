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
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int ans=1;
    for(int i=0;i<n;i++){
        ans=max(ans,(int)adj[i].size());
    }
    vector<int> dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        int ch=0;
        int mx=0,mx2=0;
        for(auto v:adj[u]){
            if(v==p){
                continue;
            }
            ch++;
            dfs(v,u);
            mx2=max(mx2,dp[v]);
            if(mx2>mx)swap(mx,mx2);
        }
        if(ch>=1){
            ans=max(ans,mx+ch-1+(u!=0));
            dp[u]=mx;
        }
        if(ch>=2){
            ans=max(ans,mx+mx2+ch-2+(u!=0));
            dp[u]=mx+ch-1;
        }
        dp[u]=max(dp[u],ch);
    };
    dfs(0,-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}