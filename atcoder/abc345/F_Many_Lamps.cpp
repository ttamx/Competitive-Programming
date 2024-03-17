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

struct DSU{
    vi p,sz;
    DSU(){}
    DSU(int n){
        init(n);
    }
    void init(int n){
        p.resize(n);
        iota(all(p),0);
        sz.assign(n,1);
    }
    int fp(int u){
        return p[u]=(u==p[u]?u:fp(p[u]));
    }
    bool merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        if(sz[u]<sz[v])swap(u,v);
        p[v]=u;
        sz[u]+=sz[v];
        return true;
    }
    bool same(int u,int v){
        return fp(u)==fp(v);
    }
    int size(int u){
        return sz[fp(u)];
    }
};

const int N=2e5+5;

int n,m,k;
vector<pii> adj[N];
int deg[N],a[N];
bool vis[N];
vi ans;
DSU dsu;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    if(k&1)cout << "No",exit(0);
    if(!k)cout << "Yes\n0\n",exit(0);
    dsu.init(n+1);
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        if(dsu.merge(u,v)){
            adj[u].emplace_back(v,i);
            adj[v].emplace_back(u,i);
            deg[u]++,deg[v]++;
        }
    }
    queue<int> q;
    for(int i=1;i<=n;i++)if(deg[i]==1)q.emplace(i);
    int cnt=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=true;
        for(auto [v,i]:adj[u])if(!vis[v]){
            if(!a[u]){
                ans.emplace_back(i);
                a[u]^=1;
                a[v]^=1;
                cnt+=a[v]*2;
                if(cnt==k){
                    cout << "Yes\n";
                    cout << sz(ans) << "\n";
                    for(auto x:ans)cout << x << " ";
                    exit(0);
                }
            }
            if(--deg[v]==1)q.emplace(v);
        }
    }
    cout << "No";
}