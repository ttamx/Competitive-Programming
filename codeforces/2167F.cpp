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
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int base=0;
    ll ans=0;
    vector<int> sz(n);
    function<void(int,int)> dfs=[&](int u,int p){
        sz[u]=1;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            sz[u]+=sz[v];
        }
        if(sz[u]>=k)base++;
    };
    function<void(int,int)> dfs2=[&](int u,int p){
        if(sz[u]>=k)base--;
        ans+=base+1;
        for(auto v:adj[u]){
            if(v==p)continue;
            if(n-sz[v]>=k)base++;
            dfs2(v,u);
            if(n-sz[v]>=k)base--;
        }
        if(sz[u]>=k)base++;
    };
    dfs(0,-1);
    dfs2(0,-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}