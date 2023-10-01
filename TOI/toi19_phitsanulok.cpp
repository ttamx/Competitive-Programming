#include<bits/stdc++.h>

using namespace std;

const int N=80005;
const int M=(1<<19)+5;

int n,s;
int dp[M];
bool vis[M];
vector<pair<int,int>> adj[M];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
vector<int> vec;
int ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    for(int i=1;i<=n;i++){
        int u=0,v=0,w;
        cin >> w;
        for(int j=0;j<s;j++){
            int x;
            cin >> x;
            if(x==-1)u+=(1<<j);
            else if(x==1)v+=(1<<j);
        }
        adj[u].emplace_back(v,w);
        vec.emplace_back(u);
    }
    for(int i=1;i<1<<s;i++){
        for(int j=0;j<s;j++){
            if(i&(1<<j)){
                adj[i].emplace_back(i^(1<<j),0);
            }
        }
    }
    for(int i=0;i<1<<s;i++)dp[i]=2e9;
    dp[0]=0;
    pq.emplace(0,0);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(d+w>=dp[v])continue;
            dp[v]=d+w;
            pq.emplace(d+w,v);
        }
    }
    for(auto x:vec)ans=max(ans,dp[x]==2e9?0:dp[x]);
    cout << ans;
}