#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=LLONG_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    vector<vector<ll>> dist(n,vector<ll>(n,INF));
    for(int i=0;i<n;i++)dist[i][i]=0;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
        dist[u][v]=dist[v][u]=min(dist[u][v],(ll)w);
    }
    for(int x=0;x<n;x++){
        for(int u=0;u<n;u++){
            for(int v=0;v<n;v++){
                dist[u][v]=min(dist[u][v],dist[u][x]+dist[x][v]);
            }
        }
    }
    for(int s=0;s<n;s++){
        vector<int> cnt(n);
        for(int u=0;u<n;u++){
            for(auto [v,w]:adj[u]){
                if(dist[s][v]+w==dist[s][u]){
                    cnt[u]++;
                }
            }
        }
        for(int t=s+1;t<n;t++){
            int ans=0;
            for(int u=0;u<n;u++){
                if(dist[s][u]+dist[u][t]==dist[s][t]){
                    ans+=cnt[u];
                }
            }
            cout << ans << " ";
        }
    }
    cout << "\n";
}