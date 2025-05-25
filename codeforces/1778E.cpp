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

const int B=30;

struct Gauss{
    array<uint32_t,B> basis;
    void insert(uint32_t x){
        for(int i=B-1;i>=0;i--){
            if(!(x>>i&1))continue;
            if(!basis[i]){
                basis[i]=x;
                return;
            }
            x^=basis[i];
        }
    }
    int32_t query(uint32_t x=0){
        for(int i=B-1;i>=0;i--){
            if(x>>i&1)continue;
            x^=basis[i];
        }
        return x;
    }
    void merge(const Gauss &o){
        for(auto x:o.basis){
            insert(x);
        }
    }
    void clear(){
        basis.fill(0);
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int timer=-1;
    vector<int> par(n,-1),tin(n),tout(n);
    vector<vector<pair<int,int>>> ch(n);
    vector<Gauss> dp(n),pre(n),suf(n),up(n);
    function<void(int)> dfs=[&](int u){
        tin[u]=++timer;
        for(auto v:adj[u]){
            if(v==par[u])continue;
            par[v]=u;
            dfs(v);
            ch[u].emplace_back(tout[v],v);
        }
        for(auto v:adj[u]){
            pre[v]=dp[u];
            dp[u].merge(dp[v]);
        }
        dp[u].clear();
        reverse(adj[u].begin(),adj[u].end());
        for(auto v:adj[u]){
            suf[v]=dp[u];
            dp[u].merge(dp[v]);
        }
        reverse(adj[u].begin(),adj[u].end());
        dp[u].insert(a[u]);
        tout[u]=timer;
    };
    function<void(int)> dfs2=[&](int u){
        for(auto v:adj[u]){
            if(v==par[u])continue;
            up[v]=up[u];
            up[v].insert(a[u]);
            up[v].merge(pre[v]);
            up[v].merge(suf[v]);
            dfs2(v);
        }
    };
    dfs(0);
    dfs2(0);
    int q;
    cin >> q;
    while(q--){
        int r,u;
        cin >> r >> u;
        r--,u--;
        if(u==r){
            Gauss cur=dp[u];
            cur.merge(up[u]);
            cout << cur.query() << "\n";
        }else if(tin[u]<=tin[r]&&tout[r]<=tout[u]){
            int v=lower_bound(ch[u].begin(),ch[u].end(),make_pair(tin[r],0))->second;
            Gauss cur=up[u];
            cur.insert(a[u]);
            cur.merge(pre[v]);
            cur.merge(suf[v]);
            cout << cur.query() << "\n";
        }else{
            cout << dp[u].query() << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}