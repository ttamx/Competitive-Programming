#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=24;
const int S=1<<N;
const int INF=1e9;

int n,m,nn;
int id[N];
vector<pair<int,int>> adj[N];
ll dp1[S],dp2[S];
int dp[S][N];
int dist[N];
int s1,t1,s2,t2;
ll ans=0;

void calc(ll *store,int s,int t){
    for(int i=0;i<n;i++){
        dist[i]=INF;
    }
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    dist[s]=0;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
    dp[1<<s][s]=1;
    for(int mask=0;mask<nn;mask++){
        for(int u=0;u<n;u++){
            if(dp[mask][u]==0)continue;
            if(u==t){
                store[mask]+=dp[mask][u];
                continue;
            }
            for(auto [v,w]:adj[u]){
                if(mask>>v&1)continue;
                if(dist[u]+w==dist[v]){
                    dp[mask|(1<<v)][v]+=dp[mask][u];
                }
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    nn=1<<n;
    vector<tuple<int,int,int>> edges(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    cin >> s1 >> t1 >> s2 >> t2;
    s1--,t1--,s2--,t2--;
    for(auto &[u,v,w]:edges){
        u=id[u],v=id[v];
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    calc(dp1,s1,t1);
    calc(dp2,s2,t2);
    for(int i=0;i<n;i++){
        for(int mask=0;mask<nn;mask++){
            if(mask>>i&1){
                dp1[mask]+=dp1[mask^(1<<i)];
            }
        }
    }
    for(int mask=0;mask<nn;mask++){
        ans+=1LL*dp1[mask]*dp2[(nn-1)^mask];
    }
    cout << ans << "\n";
}