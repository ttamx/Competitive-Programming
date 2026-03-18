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
    vector<int> a(n),b(n),c(n);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i] >> c[i];
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    vector<vector<int>> adj(n),rev(n);
    vector<pair<int,int>> edges;
    auto link=[&](int u,int v){
        edges.emplace_back(u,v);
        adj[u].emplace_back(v);
        rev[v].emplace_back(u);
    };
    for(int t=0;t<3;t++){
        sort(ord.begin(),ord.end(),[&](int i,int j){return a[i]<a[j];});
        for(int i=1;i<n;i++){
            int u=ord[i],v=ord[i-1];
            link(u,v);
            if(a[u]==a[v])link(v,u);
        }
        swap(a,b);
        swap(b,c);
    }
    vector<int> st;
    vector<bool> vis(n);
    vector<int> scc(n,-1),sz(n);
    int buf=0;
    function<void(int)> dfs=[&](int u){
        if(vis[u])return;
        vis[u]=true;
        for(auto v:adj[u])dfs(v);
        st.emplace_back(u);
    };
    function<void(int)> dfs2=[&](int u){
        scc[u]=buf;
        sz[buf]++;
        for(auto v:rev[u])if(scc[v]==-1)dfs2(v);
    };
    for(int i=0;i<n;i++)dfs(i);
    reverse(st.begin(),st.end());
    vis.assign(n,false);
    for(auto u:st)if(scc[u]==-1){
        dfs2(u);
        buf++;
    }
    vector<int> deg(n);
    for(auto [u,v]:edges){
        u=scc[u],v=scc[v];
        if(u!=v)deg[v]++;
    }
    int ans=0;
    for(int i=0;i<n;i++)if(!deg[i])ans+=sz[i];
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}