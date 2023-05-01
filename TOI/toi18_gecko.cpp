#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=20005;
const int M=2e5+5;

int n,m,k,p,cnt;
int w[M],dp[N],pa[N];
p2 e[M];
vector<int> g,adj[N];
priority_queue<p2,vector<p2>,greater<p2>> pq;
deque<int> ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k >> p;
    for(int i=0;i<n;i++)dp[i]=2e9;
    g.resize(k);
    for(auto &x:g)cin >> x;
    for(int i=1;i<=m;i++){
        auto &[u,v]=e[i];
        cin >> u >> v >> w[i];
        adj[u].emplace_back(i);
        adj[v].emplace_back(i);
    }
    auto go=[&](int x,int i){
        auto &[u,v]=e[i];
        return x^u^v;
    };
    pq.emplace(0,p);
    dp[p]=0;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(pa[u])ans.emplace_front(pa[u]);
        for(auto i:adj[u]){
            int v=go(u,i);
            if(d+w[i]>=dp[v])continue;
            pa[v]=i;
            dp[v]=d+w[i];
            pq.emplace(dp[v],v);
        }
    }
    for(auto &u:g)cout << dp[u] << ' ';
    cout << '\n';
    cout << ans.size() << '\n';
    for(auto i:ans){
        auto &[u,v]=e[i];
        cout << u << ' ' << v << '\n';
    }
}