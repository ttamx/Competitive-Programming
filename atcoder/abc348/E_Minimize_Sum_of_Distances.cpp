#include<bits/stdc++.h>
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

const int N=1e5+5;

int n;
vi adj[N];
ll a[N],sz[N];
ll sum[N],dp[N];
ll ans=LINF,cur,tot;

void dfs(int u,int p=0){
    sz[u]=1;
    sum[u]=a[u];
    for(auto v:adj[u])if(v!=p){
        dfs(v,u);
        sz[u]+=sz[v];
        sum[u]+=sum[v];
        dp[u]+=dp[v]+sum[v];
    }
}

void dfs2(int u,int p=0){
    ans=min(ans,cur);
    for(auto v:adj[u])if(v!=p){
        cur+=tot-2*sum[v];
        dfs2(v,u);
        cur-=tot-2*sum[v];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)cin >> a[i],tot+=a[i];
    dfs(1);
    cur=dp[1];
    dfs2(1);
    cout << ans;
}