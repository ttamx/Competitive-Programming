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
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> disc(n),low(n),siz(n);
    int timer=0;
    vector<int> bridges;
    function<void(int,int)> dfs=[&](int u,int p){
        disc[u]=low[u]=++timer;
        siz[u]=1;
        for(auto v:adj[u])if(v!=p){
            if(disc[v]){
                low[u]=min(low[u],disc[v]);
            }else{
                dfs(v,u);
                if(low[v]>disc[u]){
                    bridges.emplace_back(v);
                }
                low[u]=min(low[u],low[v]);
                siz[u]+=siz[v];
            }
        }
    };
    dfs(0,-1);
    ll ans=0;
    for(auto u:bridges){
        ans=max(ans,1LL*siz[u]*(n-siz[u]));
    }
    cout << 1LL*n*(n-1)/2-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}