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
    vector<bool> mark(n);
    vector<int> par(n);
    vector<pair<int,int>> dp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        par[u]=p;
        dp[u]={0,u};
        for(auto v:adj[u]){
            if(v!=p&&!mark[v]){
                dfs(v,u);
                dp[u]=max(dp[u],dp[v]);
            }
        }
        dp[u].first++;
    };
    vector<tuple<int,int,int>> ans;
    for(int i=0;i<n;i++){
        while(!mark[i]){
            dfs(i,-1);
            int u=dp[i].second;
            dfs(u,-1);
            int v=dp[u].second;
            int sz=0;
            for(int j=v;j!=-1;j=par[j]){
                mark[j]=true;
                sz++;
            }
            if(u<v)swap(u,v);
            ans.emplace_back(sz,u,v);
        }
    }
    sort(ans.rbegin(),ans.rend());
    for(auto [d,u,v]:ans){
        cout << d << " " << u+1 << " " << v+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}