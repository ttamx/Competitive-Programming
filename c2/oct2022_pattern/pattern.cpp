#include <vector>
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const ll mod=1e9+7;

int n,m,cnt;
ll pw[N];
ll dp[N][8];
int col[N],mp[N];
vector<int> adj[N];
bool vis[N][8];

ll dfs(int u,int c){
    if(vis[u][c])return dp[u][c];
    vis[u][c]=true;
    if(col[u]&&col[u]!=c)return dp[u][c]=0;
    if(adj[u].size()==0)return dp[u][c]=1;
    ll all=1,sub=1;
    for(auto v:adj[u]){
        ll sum=(m-cnt)*dfs(v,0)%mod;
        for(int i=1;i<=cnt;i++)sum+=dfs(v,i),sum%=mod;
        all*=sum,all%=mod;
        sub*=(sum-dfs(v,c)),sub%=mod;
    }
    dp[u][c]=all-sub+mod,dp[u][c]%=mod;
    return dp[u][c];
}

int total_pattern(int N, int M, std::vector<std::vector<int> >Path, std::vector<std::vector<int> >p)
{   
    n=N,m=M;
    for(auto v:Path)adj[v[0]].push_back(v[1]);
    for(int i=0;i<n;i++)col[i]=0;
    for(auto v:p){
        if(!mp[v[1]])mp[v[1]]=++cnt;
        col[v[0]]=mp[v[1]];
    }
    ll ans=(m-cnt)*dfs(0,0)%mod;
    for(int i=1;i<=cnt;i++)ans+=dfs(0,i),ans%=mod;
    return ans;
}
