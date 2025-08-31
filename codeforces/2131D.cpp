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
    vector<int> deg(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    if(n==2){
        cout << 0 << "\n";
        return;
    }
    int tot=count(deg.begin(),deg.end(),1);
    int ans=INF;
    vector<int> sz(n);
    function<void(int,int)> dfs=[&](int u,int p){
        sz[u]=(deg[u]==1);
        int sum=0;
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
            sz[u]+=sz[v];
            if(deg[v]>1){
                sum+=sz[v];
            }
        }
        sum+=tot-sz[u];
        ans=min(ans,sum);
    };
    for(int i=0;i<n;i++){
        if(deg[i]>1){
            dfs(i,-1);
            break;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}