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
    for(auto &x:a){
        cin >> x;
        x&=1;
    }
    vector<vector<int>> adj(n),adj2(n);
    vector<bool> good(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(a[u]&&a[v]){
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }else if(a[u]){
            if(!good[v]){
                good[v]=true;
                adj2[v].emplace_back(u);
            }else{
                adj2[u].emplace_back(v);
            }
        }else if(a[v]){
            if(!good[u]){
                good[u]=true;
                adj2[u].emplace_back(v);
            }else{
                adj2[v].emplace_back(u);
            }
        }
    }
    for(int i=0;i<n;i++){
        if(!a[i]&&!good[i]){
            cout << "NO\n";
            return;
        }
    }
    vector<bool> vis(n);
    function<int(int,int)> dfs=[&](int u,int p){
        int c=0;
        vis[u]=true;
        for(auto v:adj[u])if(v!=p){
            int x=dfs(v,u);
            c^=x^1;
            if(x){
                adj2[v].emplace_back(u);
            }else{
                adj2[u].emplace_back(v);
            }
        }
        return c;
    };
    for(int i=0;i<n;i++){
        if(a[i]&&!vis[i]){
            if(dfs(i,-1)){
                cout << "NO\n";
                return;
            }
        }
    }
    cout << "YES\n";
    vector<int> deg(n);
    for(int u=0;u<n;u++)for(auto v:adj2[u])deg[v]++;
    queue<int> q;
    for(int i=0;i<n;i++)if(!deg[i])q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        cout << u+1 << " ";
        for(auto v:adj2[u])if(--deg[v]==0)q.emplace(v);
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}