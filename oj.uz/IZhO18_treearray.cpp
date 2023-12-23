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

const int N=2e5+5;
const int K=18;

int n,m,q;
int a[N];
vector<int> adj[N];
set<int> pos[N],pos2[N];
int lv[N],pa[N][K];

void dfs(int u,int p=0){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<K;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u])if(v!=p)dfs(v,u);
}

int lca(int u,int v){
    if(lv[u]<lv[v])swap(u,v);
    for(int i=K-1;i>=0;i--)if(lv[pa[u][i]]>=lv[v])u=pa[u][i];
    if(u==v)return u;
    for(int i=K-1;i>=0;i--)if(pa[u][i]!=pa[v][i])u=pa[u][i],v=pa[v][i];
    return pa[u][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    for(int i=1;i<=m;i++)cin >> a[i];
    for(int i=1;i<=m;i++)pos[a[i]].emplace(i);
    for(int i=2;i<=m;i++)pos2[lca(a[i],a[i-1])].emplace(i);
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int i,v;
            cin >> i >> v;
            pos[a[i]].erase(i);
            if(i>1)pos2[lca(a[i],a[i-1])].erase(i);
            if(i<m)pos2[lca(a[i],a[i+1])].erase(i+1);
            a[i]=v;
            pos[a[i]].emplace(i);
            if(i>1)pos2[lca(a[i],a[i-1])].emplace(i);
            if(i<m)pos2[lca(a[i],a[i+1])].emplace(i+1);
        }else{
            int l,r,v;
            cin >> l >> r >> v;
            auto it=pos[v].lower_bound(l);
            if(it!=pos[v].end()&&*it<=r){
                cout << *it << " " << *it << "\n";
                continue;
            }
            it=pos2[v].lower_bound(l+1);
            if(it!=pos2[v].end()&&*it<=r){
                cout << *it-1 << " " << *it << "\n";
                continue;
            }
            cout << "-1 -1\n";
        }
    }
}