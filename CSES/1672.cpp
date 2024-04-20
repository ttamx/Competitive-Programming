#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;
const ll INF=LLONG_MAX/2;

int n,m,q;
ll dist[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dist[i][j]=INF;
    for(int i=1;i<=n;i++)dist[i][i]=0;
    for(int i=0;i<m;i++){
        int u,v;
        ll w;
        cin >> u >> v >> w;
        dist[u][v]=min(dist[u][v],w);
        dist[v][u]=min(dist[v][u],w);
    }
    for(int k=1;k<=n;k++){
        for(int u=1;u<=n;u++){
            for(int v=1;v<=n;v++){
                dist[u][v]=min(dist[u][v],dist[u][k]+dist[k][v]);
            }
        }
    }
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << (dist[u][v]==INF?-1LL:dist[u][v]) << "\n";
    }
}