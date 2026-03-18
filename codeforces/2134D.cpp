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
    bool ok=true;
    for(int i=0;i<n;i++){
        if(adj[i].size()>2){
            ok=false;
        }
    }
    if(ok){
        cout << -1 << "\n";
        return;
    }
    vector<pair<int,int>> a;
    vector<int> dp(n),par(n,-1),dep(n);
    function<void(int)> dfs=[&](int u){
        if(adj[u].size()>2)dp[u]=0;
        for(auto v:adj[u]){
            if(v==par[u])continue;
            dep[v]=dep[u]+1;
            par[v]=u;
            dp[v]=dp[u]+1;
            dfs(v);
        }
        if(adj[u].size()==1){
            a.emplace_back(dp[u],u);
        }
    };
    dfs(0);
    int root=max_element(dep.begin(),dep.end())-dep.begin();
    dep[root]=0;
    par[root]=-1;
    dfs(root);
    vector<bool> mark(n);
    for(int u=max_element(dep.begin(),dep.end())-dep.begin();par[u]!=-1;u=par[u]){
        for(auto v:adj[par[u]]){
            if(v!=par[par[u]]&&v!=u){
                cout << u+1 << " " << par[u]+1 << " " << v+1 << "\n";
                return;
            }
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}