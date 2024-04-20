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

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vi> adj(n);
    vector<tuple<int,int,int>> edge(m);
    for(auto &[w,u,v]:edge){
        cin >> u >> v >> w;
        u--,v--;
    }
    vi fa(n);
    iota(all(fa),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=fa[u]==u?u:fp(fa[u]);
    };
    sort(rall(edge));
    int ans,s,t;
    for(auto [w,u,v]:edge){
        int pu=fp(u),pv=fp(v);
        if(pu!=pv){
            fa[pu]=pv;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }else{
            ans=w,s=u,t=v;
        }
    }
    vi pa(n,-1);
    function<void(int,int)> dfs=[&](int u,int p){
        pa[u]=p;
        for(auto v:adj[u])if(v!=p)dfs(v,u);
    };
    for(int i=0;i<n;i++)if(pa[i]==-1)dfs(i,-1);
    vi ps,pt;
    for(int u=s;u!=-1;u=pa[u])ps.emplace_back(u);
    for(int u=t;u!=-1;u=pa[u])pt.emplace_back(u);
    int md;
    while(!ps.empty()&&!pt.empty()&&ps.back()==pt.back()){
        md=ps.back();
        ps.pop_back();
        pt.pop_back();
    }
    reverse(all(pt));
    vi res;
    for(auto x:ps)res.emplace_back(x);
    res.emplace_back(md);
    for(auto x:pt)res.emplace_back(x);
    cout << ans << " " << sz(res) << "\n";
    for(auto x:res)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}