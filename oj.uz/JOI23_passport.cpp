#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=2e5+5;
const int M=5*N;
const int inf=1e9;

int n,q;
vector<p2> adj[M];
int dist[3][M];
bool vis[M];

void link(int u,int v,int w=0){
    adj[v].emplace_back(u,w);
}

void build(int l,int r,int i){
    if(l==r)return void(link(n+i,l));
    int m=(l+r)/2;
    build(l,m,i*2);
    build(m+1,r,i*2+1);
    link(n+i,n+i*2);
    link(n+i,n+i*2+1);
}

void connect(int l,int r,int i,int x,int y,int u){
    if(y<l||r<x)return;
    if(x<=l&&r<=y)return void(link(u,n+i,1));
    int m=(l+r)/2;
    connect(l,m,i*2,x,y,u);
    connect(m+1,r,i*2+1,x,y,u);
}

void dijk(int *dist){
    priority_queue<p2,vector<p2>,greater<p2>> pq;
    for(int i=1;i<=5*n;i++)pq.emplace(dist[i],i),vis[i]=false;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u])if(d+w<dist[v]){
            pq.emplace(d+w,v);
            dist[v]=d+w;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    build(1,n,1);
    for(int i=1;i<=n;i++){
        int l,r;
        cin >> l >> r;
        connect(1,n,1,l,r,i);
    }
    for(int i=0;i<3;i++)for(int j=1;j<=5*n;j++)dist[i][j]=inf;
    dist[0][1]=dist[1][n]=0;
    dijk(dist[0]);
    dijk(dist[1]);
    for(int i=1;i<=n;i++)dist[2][i]=min(inf,dist[0][i]+dist[1][i]-(1<i&&i<n));
    dijk(dist[2]);
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << (dist[2][x]<inf?dist[2][x]:-1) << "\n";
    }
}