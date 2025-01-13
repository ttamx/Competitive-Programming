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
    vector<int> a(n);
    vector<vector<int>> adj(n);
    for(auto &x:a){
        cin >> x;
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> lz(n);
    vector<set<int>> dp(n);
    auto dfs=[&](auto &&self,int u,int p)->int {
        dp[u]={0};
        lz[u]=0;
        int res=0;
        bool bad=false;
        for(auto v:adj[u]){
            if(v==p)continue;
            res+=self(self,v,u);
            if(dp[u].size()<dp[v].size()){
                swap(dp[u],dp[v]);
                swap(lz[u],lz[v]);
            }
            for(auto x:dp[v]){
                if(dp[u].count(x^lz[u]^lz[v]^a[u])){
                    bad=true;
                }
            }
            for(auto x:dp[v]){
                dp[u].emplace(x^lz[u]^lz[v]);
            }
        }
        lz[u]^=a[u];
        if(bad){
            res++;
            dp[u].clear();
        }
        return res;
    };
    cout << dfs(dfs,0,-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}