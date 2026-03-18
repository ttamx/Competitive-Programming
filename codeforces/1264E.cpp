#include<bits/stdc++.h>

using namespace std;

using ll = long long;

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
    vector<vector<int>> adj;
    vector<C> pot,dist;
    vector<int> pre;
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
    void add_edge(int u,int v,F cap,C cost){
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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int,int>> edges;
    vector<vector<int>> a(n,vector<int>(n,-1));
    vector<vector<int>> id(n,vector<int>(n,-1));
    vector<int> deg(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        a[u][v]=1;
        a[v][u]=0;
        deg[u]++;
    }
    for(int i=0;i<n;i++){
        a[i][i]=0;
    }
    int buf=n;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i][j]==-1){
                id[i][j]=buf++;
            }
        }
    }
    int s=buf++,t=buf++;
    MinCostFlow<int,int> mcf(buf);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i][j]==-1){
                mcf.add_edge(s,id[i][j],1,0);
                mcf.add_edge(id[i][j],i,1,0);
                mcf.add_edge(id[i][j],j,1,0);
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=deg[i];j<n;j++){
            mcf.add_edge(i,t,1,j*2+1);
        }
    }
    mcf.flow(s,t);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(a[i][j]==-1){
                bool ok=false;
                for(auto e:mcf.adj[id[i][j]]){
                    if(mcf.e[e].flow==1){
                        int u=mcf.e[e].to;
                        int v=i^j^u;
                        a[u][v]=1;
                        a[v][u]=0;
                        ok=true;
                        break;
                    }
                }
                assert(ok);
            }
        }
    }
    for(auto &v:a){
        for(auto &x:v){
            cout << x;
        }
        cout << "\n";
    }
}