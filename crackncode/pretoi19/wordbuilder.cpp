#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,k;
string s,t;
vector<int> adj[N];
int dp[N];
queue<int> q;
priority_queue<int,vector<int>,greater<int>> pq[30];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    cin >> s;
    s=" "+s;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> t;
    for(int i=2;i<=n;i++)dp[i]=2e9;
    q.emplace(1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u]){
            if(dp[v]<=dp[u]+1)continue;
            dp[v]=dp[u]+1;
            q.emplace(v);
        }
    }
    for(int i=1;i<=n;i++)pq[s[i]-'A'].emplace(dp[i]);
    long long ans=0;
    for(auto x:t){
        x-='A';
        if(pq[x].empty())cout << -1,exit(0);
        ans+=pq[x].top();
        pq[x].pop();
    }
    cout << ans*2;
}