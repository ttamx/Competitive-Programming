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
    ll ans=0;
    vector<int> dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        vector<int> a;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            a.emplace_back(dp[v]);
            if(adj[u].size()==2&&adj[v].size()==2){
                ans--;
            }
        }
        if(adj[u].size()==2){
            dp[u]=1;
            ans+=a[0];
        }else if(adj[u].size()==3){
            ans+=1LL*a[0]*a[1];
            dp[u]=a[0]+a[1];
        }
    };
    for(int i=0;i<n;i++){
        if(adj[i].size()==1){
            dfs(i,-1);
            cout << ans << "\n";
            return;
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}