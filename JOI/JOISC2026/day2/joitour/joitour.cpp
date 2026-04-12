#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;
const int Q=2005;

int n,m,q;
int a[N];
vector<int> adj[N];
int dist[N][N];
int dp[N][N][2];
vector<pair<int,int>> ord[N];
bool vis[N];
ll ans[2*N];

void dfs(int u,int p,int i){
    for(auto v:adj[u])if(v!=p){
        dist[i][v]=dist[i][u]+1;
        dfs(v,u,i);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        dfs(i,0,i);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            ord[dist[i][j]].emplace_back(i,j);
        }
    }
    cin >> m;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        dp[u][v][0]++;
        dp[v][u][0]++;
    }
    for(int d=n-1;d>=1;d--){
        for(auto [u,v]:ord[d]){
            ans[a[u]+a[v]]+=dp[u][v][0]+dp[u][v][1];
            for(auto x:adj[v]){
                if(dist[u][x]!=d-1)continue;
                dp[u][x][0]+=dp[u][v][0];
            }
            for(auto x:adj[u]){
                if(dist[x][v]!=d-1)continue;
                dp[x][v][1]+=dp[u][v][0]+dp[u][v][1];
            }
        }
    }
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << ans[x]/2 << "\n";
    }
}