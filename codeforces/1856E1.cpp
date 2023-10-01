#include<bits/stdc++.h>

using namespace std;

const int N=5005;

int n;
int sz[N];
vector<int> adj[N];

int dfs(int u){
    int sum=0;
    bitset<N/2> dp;
    dp[0]=1;
    for(auto v:adj[u]){
        sum+=dfs(v);
        dp|=dp<<sz[v];
        sz[u]+=sz[v];
    }
    int mx=0;
    for(int i=0;i<=sz[u]/2;i++)if(dp[i])mx=max(mx,i*(sz[u]-i));
    sum+=mx;
    sz[u]++;
    return sum;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++){
        int p;
        cin >> p;
        adj[p].emplace_back(i);
    }
    cout << dfs(1);
}