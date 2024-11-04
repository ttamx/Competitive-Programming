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
    int n,m;
    cin >> n >> m;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        deg[v]++;
    }
    vector<int> bfs;
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            bfs.emplace_back(i);
        }
    }
    for(int i=0;i<n;i++){
        int u=bfs[i];
        for(auto v:adj[u]){
            if(--deg[v]==0){
                bfs.emplace_back(v);
            }
        }
    }
    ll ans=0;
    for(;ans<n;ans++){
        if(a==vector<ll>(n,0)){
            break;
        }
        for(int i=n-1;i>=0;i--){
            int u=bfs[i];
            if(a[u]>0){
                a[u]--;
                for(auto v:adj[u]){
                    a[v]++;
                }
            }
        }
    }
    for(auto u:bfs){
        for(auto v:adj[u]){
            a[v]+=a[u];
            a[v]%=MOD;
        }
    }
    ans+=a[bfs.back()];
    ans%=MOD;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}