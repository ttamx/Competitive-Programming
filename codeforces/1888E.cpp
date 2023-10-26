#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=2e5+5;

int n,t,k;
vector<p2> adj[N];
int a[N];
vector<int> vec[N];
bool vis[N];
int dp[N];
priority_queue<p2,vector<p2>,greater<p2>> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> t;
    for(int i=1;i<=t;i++){
        int m;
        cin >> m;
        while(m--){
            int u,v;
            cin >> u >> v;
            adj[u].emplace_back(v,i);
            adj[v].emplace_back(u,i);
        }
    }
    cin >> k;
    for(int i=1;i<=k;i++){
        cin >> a[i];
        vec[a[i]].emplace_back(i);
    }
    for(int i=2;i<=n;i++)dp[i]=k+1;
    pq.emplace(0,1);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,id]:adj[u])if(!vis[v]){
            auto it=upper_bound(vec[id].begin(),vec[id].end(),d);
            if(it!=vec[id].end()&&*it<dp[v]){
                dp[v]=*it;
                pq.emplace(dp[v],v);
            }
        }
    }
    cout << (dp[n]>k?-1:dp[n]);
}