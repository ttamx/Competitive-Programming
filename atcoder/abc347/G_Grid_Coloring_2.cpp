#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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
    }
    void addEdge(int u,int v,F cap,C cost){
        cerr << u << " -> " << v << " : " << cap << " " << cost << "\n";
        adj[u].emplace_back(sz(e));
        e.emplace_back(v,cap,cost);
        adj[v].emplace_back(sz(e));
        e.emplace_back(u,0,-cost);
    }
    bool dijkstra(int s,int t){
        using P=pair<C,int>;
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
        for(int t=0;t<n;t++)for(int i=0;i<sz(e);i++)if(e[i].getcap()>0){
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

const int N=25;

int n;
int a[N][N],b[N][N];
ll dp[N][N],dp2[N][N];
MinCostFlow<ll,ll> mf;

int encode(int i,int j){
    i--,j--;
    return i*n+j;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin >> a[i][j];
        }
    }
    dp[0][1]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    dp2[n+1][n]=1;
    for(int i=n;i>=1;i--){
        for(int j=n;j>=1;j--){
            dp2[i][j]=dp2[i+1][j]+dp2[i][j+1];
        }
    }
    mf.init(n*n*5+4);
    for(int i=1;i<=n;i++){
        for(int j=2;j<=n;j++){
            int u=encode(i,j-1)*5,v=encode(i,j)*5;
            ll flow=dp[i][j-1]*dp2[i][j];
            for(int x=1;x<=5;x++)if(a[i][j-1]==0||a[i][j-1]==x){
                for(int y=1;y<=5;y++)if(a[i][j]==0||a[i][j]==y){
                    mf.addEdge(u+x-1,v+y-1,flow,(x-y)*(x-y));
                }
            }
        }
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=n;j++){
            int u=encode(i-1,j)*5,v=encode(i,j)*5;
            ll flow=dp[i-1][j]*dp2[i][j];
            for(int x=1;x<=5;x++)if(a[i-1][j]==0||a[i-1][j]==x){
                for(int y=1;y<=5;y++)if(a[i][j]==0||a[i][j]==y){
                    mf.addEdge(u+x-1,v+y-1,flow,(x-y)*(x-y));
                }
            }
        }
    }
    int s=n*n*5,t=s+1,s2=s+2,t2=t+2;
    for(int x=1;x<=5;x++)if(a[1][1]==0||a[1][1]==x){
        mf.addEdge(s,x-1,dp[n][n],0);
    }
    for(int x=1;x<=5;x++)if(a[n][n]==0||a[n][n]==x){
        mf.addEdge(encode(n,n)+x-1,t,dp[n][n],0);
    }
    mf.addEdge(s2,s,dp[n][n],0);
    mf.addEdge(t,t2,dp[n][n],0);
    cout << dp[n][n] << "\n";
    auto [x,y]=mf.flow(s2,t2);
    cerr << x << " " << y;
    cout << x << " " << y << "\n";
    for(auto e:mf.e){
        if(e.flow>0&&e.to<n*n){
            int u=e.to/5,val=e.to%5+1;
            int i=u/n+1,j=u%n+1;
            b[i][j]=val;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cout << b[i][j] << " \n"[j==n];
        }
    }
}