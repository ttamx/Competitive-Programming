#include<bits/stdc++.h>

using namespace std;

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

void impossible(){
    cout << "IMPOSSIBLE\n";
    exit(0);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int s=2*n*m+k,t=2*n*m+k+1;
    MinCostFlow<int,int> mcf(2*n*m+k+2);
    int base=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='0')continue;
            int x=a[i][j]-'1';
            int u=(i*m+j)*2;
            int v=u+1;
            mcf.add_edge(u,v,x,-1);
            mcf.add_edge(u,v,8-x,+1);
            base+=x;
        }
    }
    int hor=0,ver=0;
    for(int i=0;i<k;i++){
        char c;
        int x,y,z;
        cin >> c >> x >> y >> z;
        x--,y--;
        int u=2*n*m+i;
        if(c=='H'){
            for(y++;y<m&&a[x][y]>'0';y++){
                z--;
                if(z<0)impossible();
                mcf.add_edge(u,(x*m+y)*2,z,0);
            }
            mcf.add_edge(s,u,z,0);
            hor+=z;
        }else{
            for(x++;x<n&&a[x][y]>'0';x++){
                z--;
                if(z<0)impossible();
                mcf.add_edge((x*m+y)*2+1,u,z,0);
            }
            mcf.add_edge(u,t,z,0);
            ver+=z;
        }
    }
    auto [flow,cost]=mcf.flow(s,t);
    if(hor!=ver||flow!=hor)impossible();
    cout << base+cost << "\n";
}