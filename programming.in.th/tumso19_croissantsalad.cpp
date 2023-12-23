#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
        ll cap;
        Edge(int _to,ll _cap):to(_to),cap(_cap){}
    };
    int n;
    ll U;
    vector<Edge> e;
    vector<vi> adj;
    vi ptr,lvl;
    Dinic(int n=0){
        init(n);
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
        e.emplace_back(u,0);
    }
    ll dfs(int u,int t,ll f){
        if(u==t||!f)return f;
        for(int &i=ptr[u];i<sz(adj[u]);i++){
            int j=adj[u][i];
            if(lvl[e[j].to]==lvl[u]+1){
                if(ll p=dfs(e[j].to,t,min(f,e[j].cap))){
                    e[j].cap-=p;
                    e[j^1].cap+=p;
                    return p;
                }
            }
        }
        return 0;
    }
    ll flow(int s,int t){
        ll flow=0;
        for(ll L=1ll<<63-__builtin_clzll(U);L>0;L>>=1)do{
            lvl=ptr=vi(n);
            vi q{s};
            lvl[s]=1;
            for(int i=0;i<sz(q);i++){
                int u=q[i];
                for(auto j:adj[u])if(!lvl[e[j].to]&&e[j].cap>=L){
                    q.emplace_back(e[j].to);
                    lvl[e[j].to]=lvl[u]+1;
                }
            }
            while(ll p=dfs(s,t,LINF))flow+=p;
        }while(lvl[t]);
        return flow;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    Dinic mf(2*n+2);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        mf.addEdge(u,v+n,1);
    }
    for(int i=0;i<n;i++)mf.addEdge(2*n,i,1);
    for(int i=0;i<n;i++)mf.addEdge(i+n,2*n+1,1);
    cout << n+m-2*mf.flow(2*n,2*n+1);
}