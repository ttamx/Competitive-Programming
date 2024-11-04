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
    vector<tuple<int,int,int>> edges(m);
    vector<vector<pair<int,int>>> adj(n);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    auto dijkstra=[&](int s){
        vector<ll> dist(n,LINF);
        priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
        dist[s]=0LL;
        pq.emplace(0LL,s);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(d>dist[u])continue;
            for(auto [v,w]:adj[u]){
                if(d+w<dist[v]){
                    dist[v]=d+w;
                    pq.emplace(dist[v],v);
                }
            }
        }
        return dist;
    };
    auto dist1=dijkstra(0);
    auto dist2=dijkstra(n-1);
    ll sp=dist1[n-1];
    vector<vector<pair<int,int>>> adj2(n);
    for(int i=0;i<m;i++){
        auto &[u,v,w]=edges[i];
        if(dist1[u]+w+dist2[v]==sp||dist1[v]+w+dist2[u]==sp){
            adj2[u].emplace_back(v,i);
            adj2[v].emplace_back(u,i);
        }
    }
    vector<bool> bridge(m);
    vector<int> disc(n),low(n);
    int timer=0;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=low[u]=++timer;
        for(auto [v,i]:adj2[u]){
            if(disc[v]==0){
                dfs(v,u);
                low[u]=min(low[u],low[v]);
                if(low[v]>disc[u]){
                    bridge[i]=true;
                }
            }else if(v!=p){
                low[u]=min(low[u],disc[v]);
            }
        }
    };
    dfs(0,-1);
    for(int i=0;i<m;i++){
        cout << (bridge[i]?"Yes":"No") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}