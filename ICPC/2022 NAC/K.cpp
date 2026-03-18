#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<int,int,int,int>;

const int N=55;
const ll INF=LLONG_MAX/2;

int n,k,m;
bool mark[N];
ll dist[N][N][3];
vector<pair<int,char>> adj[N],rev[N];
priority_queue<T,vector<T>,greater<T>> pq;

inline void push(int d,int x,int y,int t){
    if(dist[x][y][t]>d){
        dist[x][y][t]=d;
        pq.emplace(d,x,y,t);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> k >> m;
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        mark[x]=true;
    }
    for(int u=1;u<=n;u++){
        for(int v=1;v<=n;v++){
            for(int i=0;i<3;i++){
                dist[u][v][i]=INF;
            }
        }
    }
    for(int i=0;i<m;i++){
        int u,v;
        char c;
        cin >> u >> c >> v;
        adj[u].emplace_back(v,c);
    }
    push(0,1,1,0);
    while(!pq.empty()){
        auto [d,u1,u2,t]=pq.top();
        pq.pop();
        if(d>dist[u1][u2][t])continue;
        if(t&&mark[u1]&&mark[u2]){
            cout << d << "\n";
            exit(0);
        }
        for(auto [v1,c1]:adj[u1]){
            for(auto [v2,c2]:adj[u2]){
                if(c1==c2){
                    if(t==1){
                        if(isupper(c1)){
                            push(d+2,v1,v2,2);
                        }
                    }else{
                        push(d+2,v1,v2,t);
                    }
                }else if(!isupper(c1)&&!isupper(c2)&&t!=1){
                    push(d+2,v1,v2,2);
                }
            }
        }
        for(auto [v1,c1]:adj[u1]){
            if(!isupper(c1)){
                push(d+1,v1,u2,max(t,1));
            }
        }
        if(t==2){
            for(auto [v2,c2]:adj[u2]){
                if(!isupper(c2)){
                    push(d+1,u1,v2,2);
                }
            }
        }
    }
    cout << -1 << "\n";
}