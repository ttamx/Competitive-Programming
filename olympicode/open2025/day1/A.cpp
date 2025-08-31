#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
vector<pair<int,int>> adj[N];
ll speed[N];
ll s[N],dp[N],up[N];
ll tot=1e12+100;
bool flag;

void dfs(int u,int p){
    dp[u]=s[u];
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[u]=min(dp[u],dp[v]-w);
    }
}

void dfs2(int u,int p){
    if(dp[u]>=0&&up[u]>=0){
        flag=true;
    }
    up[u]=min(up[u],s[u]);
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        up[v]=up[u];
    }
    for(int t=0;t<2;t++){
        ll cur=tot;
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            up[v]=min(up[v],cur);
            cur=min(cur,dp[v]-w);
        }
        reverse(adj[u].begin(),adj[u].end());
    }
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        if(up[v]>=0&&dp[v]>=0&&up[v]+dp[v]>=w){
            flag=true;
        }
        up[v]-=w;
        dfs2(v,u);
    }
}

bool check(ll mid){
    for(int i=1;i<=n;i++){
        s[i]=speed[i]?speed[i]*mid:tot;
    }
    dfs(1,0);
    flag=false;
    up[1]=tot;
    dfs2(1,0);
    return flag;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=0;i<m;i++){
        int x,sp;
        cin >> x >> sp;
        if(speed[x]==0||sp<speed[x]){
            speed[x]=sp;
        }
    }
    ll l=0,r=tot;
    while(l<r){
        ll mid=(l+r)/2;
        if(check(mid))r=mid;
        else l=mid+1;
    }
    cout << l << "\n";
}