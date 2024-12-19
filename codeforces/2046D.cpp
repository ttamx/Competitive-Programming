#include "template.hpp"
#include "graph/graph-base.hpp"
#include "graph/strongly-connected-component.hpp"

/**
 * Author: Teetat T.
 * Date: 2024-03-31
 * Description: minimum-cost flow algorithm.
 * Time: $O(FE\log{V})$ where $F$ is max flow.
 */

template<class F,class C>
struct MinCostFlow{
    struct Edge{
        int to;
        F flow,cap;
        C cost;
        Edge(int _to,F _cap,C _cost):to(_to),flow(0),cap(_cap),cost(_cost){}
        F getcap(){
            return cap-flow;
        }
    };
    int n;
    vector<Edge> e;
    vector<vi> adj;
    vector<C> pot,dist;
    vi pre;
    bool neg;
    const F FINF=numeric_limits<F>::max()/2;
    const C CINF=numeric_limits<C>::max()/2;
    MinCostFlow(){}
    MinCostFlow(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        e.clear();
        adj.assign(n,{});
        neg=false;
    }
    void addEdge(int u,int v,F cap,C cost){
        adj[u].emplace_back(e.size());
        e.emplace_back(v,cap,cost);
        adj[v].emplace_back(e.size());
        e.emplace_back(u,0,-cost);
        if(cost<0)neg=true;
    }
    bool dijkstra(int s,int t){
        using P = pair<C,int>;
        dist.assign(n,CINF);
        pre.assign(n,-1);
        priority_queue<P,vector<P>,greater<P>> pq;
        dist[s]=0;
        pq.emplace(0,s);
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(dist[u]<d)continue;
            for(int i:adj[u]){
                int v=e[i].to;
                C ndist=d+pot[u]-pot[v]+e[i].cost;
                if(e[i].getcap()>0&&dist[v]>ndist){
                    pre[v]=i;
                    dist[v]=ndist;
                    pq.emplace(ndist,v);
                }
            }
        }
        return dist[t]<CINF;
    }
    pair<F,C> flow(int s,int t){
        F flow=0;
        C cost=0;
        pot.assign(n,0);
        if(neg)for(int t=0;t<n;t++)for(int i=0;i<e.size();i++)if(e[i].getcap()>0){
            int u=e[i^1].to,v=e[i].to;
            pot[v]=min(pot[v],pot[u]+e[i].cost);
        } // Bellman-Ford
        while(dijkstra(s,t)){
            for(int i=0;i<n;i++)pot[i]+=dist[i];
            F aug=FINF;
            for(int u=t;u!=s;u=e[pre[u]^1].to){
                aug=min(aug,e[pre[u]].getcap());
            } // find bottleneck
            for(int u=t;u!=s;u=e[pre[u]^1].to){
                e[pre[u]].flow+=aug;
                e[pre[u]^1].flow-=aug;
            } // push flow
            flow+=aug;
            cost+=aug*pot[t];
        }
        return {flow,cost};
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    Graph<void,true> g(n);
    vector<pair<int,int>> e(m);
    for(auto &[u,v]:e){
        cin >> u >> v;
        u--,v--;
        g.add_edge(u,v);
    }
    if(a==vector<int>(0,n)){
        cout << "YES\n";
        return;
    }
    auto [k,scc]=strongly_connected_component(g);
    MinCostFlow<ll,ll> mcf(k*3+2);
    int s=k*3,t=s+1;
    vector<int> sz(k);
    for(int i=0;i<n;i++){
        sz[scc[i]]+=a[i];
    }
    for(int i=0;i<k;i++){
        mcf.addEdge(s,i*3,sz[i],0);
        mcf.addEdge(i*3,i*3+1,1,1);
        mcf.addEdge(i*3,i*3+2,INF,0);
        mcf.addEdge(i*3+1,i*3+2,1,-INF);
        mcf.addEdge(i*3+1,i*3+2,INF,0);
        mcf.addEdge(i*3+2,t,INF,0);
    }
    for(auto [u,v]:e){
        u=scc[u],v=scc[v];
        if(u!=v){
            mcf.addEdge(u*3+2,v*3+1,INF,0);
        }
    }
    auto [f,c]=mcf.flow(s,t);
    if(c+1LL*INF*(k-1)>=0){
        cout << -1 << "\n";
    }else{
        cout << c+1LL*INF*k << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}