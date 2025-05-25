#include<bits/stdc++.h>

using namespace std;

using T = tuple<int,int,int,int>;

const int N=105;
const int F=105;
const int INF=INT_MAX/2;

int n,m,st,ed,mf;
int p[N];
vector<pair<int,int>> adj[N];
priority_queue<T,vector<T>,greater<T>> pq;
int dp[N][F][2];
bool vis[N][F][2];

void update(int u,int f,int c,int val){
    if(val<dp[u][f][c]){
        dp[u][f][c]=val;
        pq.push({val,u,f,c});
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> p[i];
    }
    cin >> st >> ed >> mf;
    cin >> m;
    for(int i=1;i<=m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    for(int u=1;u<=n;u++){
        for(int f=0;f<=mf;f++){
            for(int c=0;c<2;c++){
                dp[u][f][c]=INF;
            }
        }
    }
    update(st,0,0,0);
    while(!pq.empty()){
        auto [d,u,f,c]=pq.top();
        pq.pop();
        if(vis[u][f][c])continue;
        vis[u][f][c]=true;
        for(auto [v,w]:adj[u]){
            if(f>=w){
                update(v,f-w,c,d);
            }
        }
        if(f+1<=mf){
            update(u,f+1,c,d+p[u]);
        }
        if(c==0){
            update(u,mf,1,d);
        }
    }
    cout << dp[ed][mf][1];
}