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
    int n;
    cin >> n;
    vector<pii> edge;
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        edge.emplace_back(i,p-1);
    }
    string s;
    cin >> s;
    vi fa(n),t(n);
    iota(all(fa),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    for(int i=0;i<n;i++){
        if(s[i]=='S')t[i]=1;
        if(s[i]=='P')t[i]=2;
    }
    int ans=0;
    vector<vi> dp(n,vi(2));
    vector<vi> adj(n);
    vi vis(n);
    for(auto [u,v]:edge){
        u=fp(u),v=fp(v);
        if(t[u]>0&&t[u]==t[v]){
            fa[u]=v;
        }else if(t[u]==t[v]){
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }else if(t[u]+t[v]==3){
            ans++;
        }else{
            if(!t[v])swap(u,v);
            dp[u][t[v]-1]++;
        }
    }
    function<void(int,int)> dfs=[&](int u,int p){
        vis[u]=1;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            dp[u][0]+=min(dp[v][0],dp[v][1]+1);
            dp[u][1]+=min(dp[v][0]+1,dp[v][1]);
        }
    };
    for(int i=0;i<n;i++)if(!vis[i]){
        dfs(i,i);
        ans+=min(dp[i][0],dp[i][1]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}