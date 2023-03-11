#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const ll mod=1e9+7;

int c,s;
ll ans=1;
ll a[N];
ll dp[N];
bool vis[N];
vector<pair<int,int>> adj[N];

void dfs(int u,int p,ll val){
    int ch=0;
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        ch++;
        dfs(v,u,(a[u]*a[v]+w+val)%mod);
    }
    if(ch==0)ans=(ans*val*2)%mod;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> c;
    for(int i=1;i<=c;i++){
        int n,m;
        cin >> n >> m;
        for(int j=1;j<=n;j++){
            adj[j].clear();
            dp[j]=1e18,vis[j]=false;
        }
        for(int j=0;j<m;j++){
            int u,v,w;
            cin >> u >> v >> w;
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        dp[1]=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
        pq.push({0,1});
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(vis[u])continue;
            vis[u]=true;
            for(auto [v,w]:adj[u]){
                if(d+w<dp[v]){
                    dp[v]=d+w;
                    pq.push({d+w,v});
                }
            }
        }
        a[i]=dp[n]*2;
    }
    cin >> s;
    for(int i=1;i<=c;i++)adj[i].clear();
    for(int i=1;i<c;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    dfs(s,0,0);
    cout << ans;
}