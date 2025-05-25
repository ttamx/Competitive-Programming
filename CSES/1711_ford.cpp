#include<bits/stdc++.h>

using namespace std;

const int N=505;

struct Edge{
    int flow,cap;
    int remain(){return cap-flow;}
};

int n,m;
vector<Edge> edges;
vector<pair<int,int>> adj[N];
bool vis[N];

int dfs(int u,int flow=1e9){
    if(u==n)return flow;
    if(vis[u])return 0;
    vis[u]=true;
    for(auto [v,i]:adj[u]){
        int rem=edges[i].remain(),cur;
        if(rem>0&&(cur=dfs(v,min(flow,rem)))>0){
            edges[i].flow+=cur;
            edges[i^1].flow-=cur;
            return cur;
        }
    }
    return 0;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        int j=edges.size();
        edges.emplace_back(Edge{0,1});
        edges.emplace_back(Edge{0,0});
        adj[u].emplace_back(v,j);
        adj[v].emplace_back(u,j^1);
    }
    int max_flow=0;
    while(true){
        for(int i=1;i<=n;i++)vis[i]=false;
        int flow=dfs(1);
        if(flow==0)break;
        max_flow+=flow;
    }
    cout << max_flow << "\n";
}