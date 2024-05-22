#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")

using namespace std;

using ll = long long;

const int N=1005;
const int K=705;
const ll INF=LLONG_MAX/2;

int n,m,k;
ll dp[K][N];
vector<int> adj[N],comp;
bool vis[N];

void dfs(int u){
    vis[u]=true;
    comp.emplace_back(u);
    for(auto v:adj[u])if(!vis[v])dfs(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    k++;
    for(int i=1;i<=k;i++)for(int j=1;j<=n;j++)dp[i][j]=-INF;
    for(int t=1;t<=m;t++){
        int e;
        cin >> e;
        for(int i=1;i<=n;i++){
            vis[i]=false;
            adj[i].clear();
        }
        for(int j=0;j<e;j++){
            int u,v;
            cin >> u >> v;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        if(t==1){
            dfs(1);
            for(auto x:comp)dp[1][x]=comp.size();
            comp.clear();
            continue;
        }
        for(int i=1;i<=n;i++)if(!vis[i]){
            dfs(i);
            for(int j=min(t,k);j>=2;j--){
                ll res=-INF;
                for(auto x:comp)res=max(res,dp[j-1][x]);
                res+=comp.size();
                for(auto x:comp)dp[j][x]=max(dp[j][x],res);
            }
            comp.clear();
        }
    }
    cout << *max_element(dp[k]+1,dp[k]+n+1);
}