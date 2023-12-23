#pragma GCC optimize("O3,unroll-loops")
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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

struct gauss{
    vi basis,pos;
    gauss():basis(20,0),pos(20,0){}
    void insert(int x,int t=0){
        for(int i=19;i>=0;i--)if(x>>i&1){
            if(!basis[i])return basis[i]=x,pos[i]=t,void();
            if(t>pos[i])swap(x,basis[i]),swap(t,pos[i]);
            x^=basis[i];
        }
    }
    bool check(int x){
        for(int i=19;i>=0;i--)if(x>>i&1){
            if(!basis[i])return false;
            x^=basis[i];
        }
        return true;
    }
};

const int N=2e5+5;
const int K=18;

int n,q;
int a[N];
vi adj[N];
int lv[N],pa[K][N];
gauss dp[N];

void dfs(int u,int p=0){
    pa[0][u]=p;
    lv[u]=lv[p]+1;
    dp[u]=dp[p];
    dp[u].insert(a[u],lv[u]);
    for(auto v:adj[u])if(v!=p)dfs(v,u);
}

int lca(int u,int v){
    if(lv[u]<lv[v])swap(u,v);
    for(int i=K-1;i>=0;i--)if(lv[pa[i][u]]>=lv[v])u=pa[i][u];
    if(u==v)return u;
    for(int i=K-1;i>=0;i--)if(pa[i][u]!=pa[i][v])u=pa[i][u],v=pa[i][v];
    return pa[0][u];
}

bool solve(int u,int v,int x){
    int l=lca(u,v);
    gauss res;
    for(int i=0;i<20;i++)if(dp[u].pos[i]>=lv[l])res.insert(dp[u].basis[i]);
    for(int i=0;i<20;i++)if(dp[v].pos[i]>=lv[l])res.insert(dp[v].basis[i]);
    return res.check(x);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    for(int i=1;i<K;i++)for(int u=1;u<=n;u++)pa[i][u]=pa[i-1][pa[i-1][u]];
    cin >> q;
    while(q--){
        int u,v,x;
        cin >> u >> v >> x;
        cout << (solve(u,v,x)?"YES":"NO") << "\n";
    }
}