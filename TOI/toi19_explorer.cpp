#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e5+5;
const int mod=1e9+7;

int n;
ll dp[N],fac[N];
vector<int> adj[N];

void dfs(int u,int p){
    dp[u]=1;
    int cnt=0;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        cnt++;
        dp[u]*=dp[v];
        dp[u]%=mod;
    }
    dp[u]*=fac[cnt];
    dp[u]%=mod;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    fac[0]=1;
    for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i,fac[i]%=mod;
    int pre=0;
    for(int i=1;i<2*n;i++){
        int cur;
        cin >> cur;
        adj[pre].emplace_back(cur);
        pre=cur;
    }
    dfs(0,0);
    cout << dp[0];
}