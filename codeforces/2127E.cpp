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
    vector<int> w(n),c(n);
    for(auto &x:w)cin >> x;
    for(auto &x:c)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1),sz(n),hv(n,-1),tin(n),tout(n),pos(n);
    int timer=-1;
    function<void(int)> dfs=[&](int u){
        tin[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        for(auto v:adj[u]){
            if(v==par[u])continue;
            par[v]=u;
            dfs(v);
            sz[u]+=sz[v];
            if(hv[u]==-1||sz[v]>sz[hv[u]]){
                hv[u]=v;
            }
        }
        tout[u]=timer;
    };
    dfs(0);
    vector<int> to_fill;
    vector<int> f(k+1);
    ll ans=0;
    function<void(int,bool)> sack=[&](int u,bool del){
        for(auto v:adj[u]){
            if(v!=par[u]&&v!=hv[u]){
                sack(v,true);
            }
        }
        if(hv[u]!=-1){
            sack(hv[u],false);
        }
        int col=0,some_col=0;
        bool flag=false;
        for(auto v:adj[u]){
            if(v==par[u]||v==hv[u])continue;
            for(int i=tin[v];i<=tout[v];i++){
                int x=pos[i];
                if(c[x]==0){
                    to_fill.emplace_back(x);
                    continue;
                }
                if(f[c[x]]){
                    if(col==0)col=c[x];
                    if(col!=c[x])flag=true;
                }
            }
            for(int i=tin[v];i<=tout[v];i++){
                int x=pos[i];
                if(c[x]==0)continue;
                some_col=c[x];
                f[c[x]]=1;
            }
        }
        if(c[u]==0){
            c[u]=col;
        }else if(col!=0&&col!=c[u]){
            flag=true;
        }
        if(flag)ans+=w[u];
        if(c[u]==0){
            c[u]=some_col;
        }
        if(c[u]){
            for(auto x:to_fill){
                c[x]=c[u];
            }
            to_fill.clear();
        }else{
            to_fill.emplace_back(u);
        }
        f[c[u]]=1;
        if(del){
            for(int i=tin[u];i<=tout[u];i++){
                f[c[pos[i]]]=0;
            }
            to_fill.clear();
        }
    };
    sack(0,false);
    for(auto &x:c){
        if(x==0){
            x=1;
        }
    }
    cout << ans << "\n";
    for(auto x:c){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}