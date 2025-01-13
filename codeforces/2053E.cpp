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
    if(n==2){
        cout << 0 << "\n";
        return;
    }
    vector<bool> leaf(n),bad(n);
    ll cnt_leaf=0;
    for(int i=0;i<n;i++){
        leaf[i]=adj[i].size()==1;
        bad[i]=leaf[i];
        cnt_leaf+=leaf[i];
    }
    ll cnt_bad=0;
    for(int i=0;i<n;i++){
        for(auto j:adj[i]){
            if(leaf[j]){
                bad[i]=true;
            }
        }
        cnt_bad+=bad[i];
    }
    ll ans=cnt_leaf*(n-cnt_leaf);
    vector<ll> sz(n),sz2(n);
    function<void(int,int)> dfs=[&](int u,int p){
        sz[u]=1;
        sz2[u]=bad[u];
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            sz[u]+=sz[v];
            sz2[u]+=sz2[v];
            if(bad[u]&&!leaf[v]){
                ll cur=n-cnt_bad;
                cur-=sz[v]-sz2[v];
                ans+=cur;
            }
            if(bad[v]){
                ans+=sz[v]-sz2[v];
            }
        }
    };
    for(int i=0;i<n;i++){
        if(adj[i].size()>1){
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
    cin >> t;
    while(t--)runcase();
}