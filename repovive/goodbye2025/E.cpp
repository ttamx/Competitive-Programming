#include<bits/stdc++.h>

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
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,c;
        cin >> u >> v >> c;
        u--,v--;
        adj[u].emplace_back(v,c);
        adj[v].emplace_back(u,c);
    }
    vector<array<int,2>> vis(n,{0,0});
    vector<array<int,2>> dp(n);
    function<int(int,int)> dfs=[&](int u,int c){
        if(vis[u][c]==1)return INF;
        if(vis[u][c]==2)return dp[u][c];
        vis[u][c]=1;
        int cur=0;
        for(auto [v,cc]:adj[u])if(c!=cc)cur=max(cur,dfs(v,cc)+1);
        vis[u][c]=2;
        return dp[u][c]=cur;
    };
    int ans=min(dfs(0,0),dfs(0,1));
    cout << (ans<n?ans+1:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}