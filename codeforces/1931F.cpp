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

struct TopologicalSort{
    int n;
    vector<vi> adj;
    TopologicalSort(){}
    TopologicalSort(int _n){
        init(_n);
    }
    void init(int _n){
        n=_n;
        adj.assign(n,vi{});
    }
    void add_edge(int u,int v){
        adj[u].emplace_back(v);
    }
    vi get_order(){
        vi deg(n),res;
        for(auto &v:adj)for(auto &x:v)deg[x]++;
        for(int i=0;i<n;i++)if(!deg[i])res.emplace_back(i);
        for(int i=0;i<sz(res);i++){
            int u=res[i];
            for(auto v:adj[u])if(!--deg[v])res.emplace_back(v);
        }
        return res;
    }
};

void runcase(){
    int n,k;
    cin >> n >> k;
    TopologicalSort ts(n);
    while(k--){
        vi a(n);
        for(auto &x:a)cin >> x,x--;
        for(int i=2;i<n;i++)ts.add_edge(a[i-1],a[i]);
    }
    cout << (sz(ts.get_order())==n?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}