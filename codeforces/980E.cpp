#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,k;
int dp[N][20];
bool used[N];
vector<int> adj[N];

void dfs(int u,int p){
    dp[u][0]=p;
    for(int i=1;i<20;++i)dp[u][i]=dp[dp[u][i-1]][i-1];
    for(auto v:adj[u])if(v!=p)dfs(v,u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<n;++i){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(n,0);
    k=n-k;
    used[0]=true;
    for(int i=n;i>0;--i){
        if(used[i])continue;
        int anc=i,cnt=1;
        for(int j=19;j>=0;--j)if(!used[dp[anc][j]])anc=dp[anc][j],cnt+=(1<<j);
        if(cnt>k)continue;
        k-=cnt;
        int cur=i;
        while(!used[cur])used[cur]=true,cur=dp[cur][0];
    }
    for(int i=1;i<=n;++i)if(!used[i])cout << i << ' ';
}