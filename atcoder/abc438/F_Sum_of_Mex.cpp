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
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1),sz(n);
    function<void(int)> dfs=[&](int u){
        sz[u]=1;
        for(auto v:adj[u])if(v!=par[u]){
            par[v]=u;
            dfs(v);
            sz[u]+=sz[v];
        }
    };
    dfs(0);
    int last=0;
    vector<bool> vis(n);
    vector<int> deg(n);
    vis[0]=true;
    ll ways=1LL*n*(n+1)/2;
    for(auto v:adj[0])ways-=1LL*sz[v]*(sz[v]+1)/2;
    ll ans=ways;
    int l=0,r=0;
    for(int i=1;i<n;i++){
        if(vis[i]){
            ans+=ways;
            continue;
        }
        vector<int> path;
        int u=i;
        while(!vis[u]){
            deg[u]++;
            deg[par[u]]++;
            path.emplace_back(u);
            u=par[u];
        }
        if(deg[u]>2)break;
        if(l==u)l=i;
        else if(r==u)r=i;
        else assert(false);
        reverse(path.begin(),path.end());
        for(auto u:path){
            sz[par[u]]-=sz[u];
            vis[u]=true;
        }
        ways=1LL*sz[l]*sz[r];
        ans+=ways;
        last=i;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}