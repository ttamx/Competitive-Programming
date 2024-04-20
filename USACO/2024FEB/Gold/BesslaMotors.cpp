#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T3 = tuple<ll,int,int>;

const int N=5e4+5;

int n,m,c,k;
ll r;
vector<pair<int,ll>> adj[N];
priority_queue<T3,vector<T3>,greater<T3>> pq;
map<int,int> dist[N];
int cnt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> c >> r >> k;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    for(int i=1;i<=c;i++){
        dist[i][i]=0;
        pq.emplace(0,i,i);
    }
    while(!pq.empty()){
        auto [d,s,u]=pq.top();
        pq.pop();
        if(cnt[u]==k||d>dist[u][s])continue;
        cnt[u]++;
        for(auto [v,w]:adj[u])if(d+w<=r&&(dist[v].find(s)==dist[v].end()||d+w<dist[v][s])){
            dist[v][s]=d+w;
            pq.emplace(d+w,s,v);
        }
    }
    int ans=0;
    for(int i=c+1;i<=n;i++)ans+=cnt[i]==k;
    cout << ans << "\n";
    for(int i=c+1;i<=n;i++)if(cnt[i]==k)cout << i << "\n";
}