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

bool check_eulerian_circuit(int n,const vector<pii> edges,const vi sources){
    vector<vi> adj(n);
    vi deg(n);
    for(auto [u,v]:edges){
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++,deg[v]++;
    }
    for(int i=0;i<n;i++)if(deg[i]&1)return false;
    vector<bool> vis(n);
    function<void(int)> dfs=[&](int u){
        vis[u]=true;
        for(auto v:adj[u])if(!vis[v])dfs(v);
    };
    for(auto s:sources)if(!vis[s])dfs(s);
    for(int i=0;i<n;i++)if(!vis[i]&&!adj[i].empty())return false;
    return true;
}

void runcase(){
    int n,m;
    cin >> n >> m;
    vi col(n);
    for(auto &x:col)cin >> x;
    vector<tuple<int,int,int>> edges(m);
    ll tot=0;
    int mn=INF;
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
        tot+=w;
        mn=min(mn,w);
    }
    auto calc=[&](int tar){
        vector<pii> e;
        vi s;
        for(auto [u,v,w]:edges)if(w>tar){
            e.emplace_back(u,v);
            if((w-tar)%2==0)e.emplace_back(u,v);
            if(col[u]!=col[v]){
                s.emplace_back(u);
                s.emplace_back(v);
            }
        }
        if(!check_eulerian_circuit(n,e,s))return LINF;
        return tot-1LL*tar*m;
    };
    ll ans=min({calc(mn),calc(mn-1),calc(mn-2)});
    cout << (ans==LINF?-1LL:ans) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}