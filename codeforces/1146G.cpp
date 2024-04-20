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

struct Dinic{
    struct Edge{
        int to;
        ll flow,cap;
        Edge(int _to,ll _cap):to(_to),flow(0),cap(_cap){}
        ll getcap(){
            return cap-flow;
        }
    };
    int n;
    ll U;
    vector<Edge> e;
    vector<vi> adj;
    vi ptr,lvl;
    Dinic(){}
    Dinic(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n,U=0;
        e.clear();
        adj.assign(n,{});
    }
    void addEdge(int u,int v,ll cap){
        U=max(U,cap);
        adj[u].emplace_back(sz(e));
        e.emplace_back(v,cap);
        adj[v].emplace_back(sz(e));
        e.emplace_back(u,0); // change 0 to cap for undirected flow
    }
    bool bfs(int s,int t,ll scale){
        lvl.assign(n,0);
        vi q{s};
        lvl[s]=1;
        for(int i=0;i<sz(q);i++){
            int u=q[i];
            for(auto j:adj[u])if(!lvl[e[j].to]&&e[j].getcap()>=scale){
                q.emplace_back(e[j].to);
                lvl[e[j].to]=lvl[u]+1;
            }
        }
        return lvl[t];
    }
    ll dfs(int u,int t,ll f){
        if(u==t||!f)return f;
        for(int &i=ptr[u];i<sz(adj[u]);i++){
            int j=adj[u][i];
            if(lvl[e[j].to]==lvl[u]+1){
                if(ll p=dfs(e[j].to,t,min(f,e[j].getcap()))){
                    e[j].flow+=p;
                    e[j^1].flow-=p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll flow(int s,int t){
        ll flow=0;
        for(ll L=1ll<<(63-__builtin_clzll(U));L>0;L>>=1) // L = 1 may be faster but it's O(V^2 E)
        while(bfs(s,t,L)){
            ptr.assign(n,0);
            while(ll p=dfs(s,t,LINF))flow+=p;
        };
        return flow;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,h,m;
    cin >> n >> h >> m;
    ll ans=n*h*h;
    Dinic mf(n*h+m+2);
    int s=mf.n-2,t=s+1;
    for(int i=0;i<n;i++){
        int id=i*h;
        for(int j=0;j<h;j++)mf.addEdge(id+j,t,(j+1)*(j+1)-j*j);
        for(int j=0;j<h-1;j++)mf.addEdge(id+j,id+j+1,INF);
    }
    for(int i=0;i<m;i++){
        int l,r,x,c;
        cin >> l >> r >> x >> c;
        l--,r--;
        int id=n*h+i;
        mf.addEdge(s,id,c);
        if(h==x)continue;
        for(int j=l;j<=r;j++)mf.addEdge(id,j*h+x,INF);
    }
    cout << ans-mf.flow(s,t);
}