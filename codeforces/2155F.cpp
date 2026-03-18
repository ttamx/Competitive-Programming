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
    int n,k,s,q;
    cin >> n >> k >> s >> q;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<vector<pair<int,int>>> col(n);
    for(int i=0;i<s;i++){
        int u,x;
        cin >> u >> x;
        u--,x--;
        col[u].emplace_back(x,u);
    }
    vector<vector<pair<int,int>>> qr(n);
    vector<int> ans(q);
    for(int i=0;i<q;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(col[u].size()<col[v].size()){
            swap(u,v);
        }
        qr[u].emplace_back(v,i);
    }
    vector<int> id(k,-1);
    vector<int> tin(n),tout(n);
    int timer=-1;
    function<void(int,int)> dfs=[&](int u,int p){
        tin[u]=++timer;
        for(auto [c,x]:col[u]){
            id[c]=x;
        }
        for(auto v:adj[u]){
            if(v==p)continue;
            for(auto &[c,x]:col[v]){
                if(id[c]!=-1){
                    x=id[c];
                }
            }
        }
        for(auto [c,x]:col[u]){
            id[c]=-1;
        }
        for(auto v:adj[u]){
            if(v==p)continue;
            dfs(v,u);
        }
        tout[u]=timer;
    };
    dfs(0,-1);
    auto in_subtree=[&](int u,int v){
        return tin[u]<=tin[v]&&tout[v]<=tout[u];
    };
    for(int u=0;u<n;u++){
        sort(qr[u].begin(),qr[u].end());
        int last=-1,pre=-1;
        for(auto [c,x]:col[u]){
            id[c]=x;
        }
        for(auto [v,i]:qr[u]){
            if(v==last){
                ans[i]=pre;
                continue;
            }
            for(auto [c,x]:col[v]){
                if(id[c]!=-1&&in_subtree(x,u)&&in_subtree(id[c],v)){
                    ans[i]++;
                }
            }
            last=v;
            pre=ans[i];
        }
        for(auto [c,x]:col[u]){
            id[c]=-1;
        }
    }
    for(auto x:ans){
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