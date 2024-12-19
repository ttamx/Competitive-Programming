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
    int n,q;
    cin >> n >> q;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            if(v!=par[u]){
                par[v]=u;
                dfs(v);
            }
        }
    };
    dfs(0);
    while(q--){
        int u,b;
        cin >> u >> b;
        u--;
        int ans=0;
        vector<int> a;
        for(int i=1;u!=0;i++,u=par[u]){
            if(i&1){
                ans++;
            }else{
                a.emplace_back(adj[u].size());
            }
        }
        sort(a.begin(),a.end());
        while(!a.empty()&&b--){
            a.pop_back();
            ans++;
        }
        for(auto x:a){
            ans+=2*x-1;
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}