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
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v,i);
        adj[v].emplace_back(u,i);
    }
    vector<pair<int,int>> dist(n,{INF,-1});
    using T = tuple<int,int,int>;
    priority_queue<T,vector<T>,greater<T>> pq;
    auto push=[&](int u,int d,int i){
        pair<int,int> v(d,i);
        if(v<dist[u]){
            dist[u]=v;
            pq.emplace(d,i,u);
        }
    };
    vector<int> disc(n),low(n);
    vector<bool> good(n);
    good[n-1]=true;
    int timer=0;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=low[u]=++timer;
        for(auto [v,i]:adj[u]){
            if(v==p)continue;
            if(!disc[v]){
                dfs(v,u);
                if(good[v])good[u]=true;
                low[u]=min(low[u],low[v]);
                if(low[v]>disc[u]&&good[v]){
                    push(u,0,i+1);
                    push(v,0,i+1);
                }
            }else{
                low[u]=min(low[u],disc[v]);
            }
        }
    };
    dfs(0,-1);
    while(!pq.empty()){
        auto [d,i,u]=pq.top();
        pq.pop();
        if(make_pair(d,i)!=dist[u])continue;
        for(auto [v,_]:adj[u]){
            push(v,d+1,i);
        }
    }
    int q;
    cin >> q;
    while(q--){
        int u;
        cin >> u;
        u--;
        cout << dist[u].second << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}