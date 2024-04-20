#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=1e18;

int n,m;
vector<pair<int,ll>> adj[N];
ll dp[N];
priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int k;
        ll p;
        cin >> k >> p;
        int u=n+i;
        for(int j=0;j<k;j++){
            int v;
            cin >> v;
            adj[u].emplace_back(v,p);
            adj[v].emplace_back(u,0);
        }
    }
    for(int i=1;i<n+m;i++)dp[i]=INF;
    pq.emplace(0,0);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dp[u])continue;
        for(auto [v,w]:adj[u])if(d+w<dp[v]){
            dp[v]=d+w;
            pq.emplace(d+w,v);
        }
    }
    cout << (dp[n-1]==INF?-1LL:dp[n-1]) << "\n";
}