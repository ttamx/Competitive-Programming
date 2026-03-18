#include<bits/stdc++.h>

using namespace std;

const int N=60;

struct Edge{
    int to,cap,flow;
    int bal(){
        return cap-flow;
    }
};

int s=0,t=25;
vector<Edge> edge;
vector<int> adj[N];
bool vis[N];

void add_edge(int u,int v,int cap){
    adj[u].emplace_back(edge.size());
    edge.emplace_back(Edge{v,cap,0});
    adj[v].emplace_back(edge.size());
    edge.emplace_back(Edge{u,cap,0});
}

int dfs(int u,int f){
    if(vis[u]||f==0)return 0;
    if(u==t)return f;
    vis[u]=true;
    for(auto i:adj[u]){
        int ff=dfs(edge[i].to,min(f,edge[i].bal()));
        if(ff>0){
            edge[i].flow+=ff;
            edge[i^1].flow-=ff;
            return ff;
        }
    }
    return 0;
}

int enc(char c){
    if(isupper(c))return c-'A';
    else return c-'a'+26;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m;
    cin >> m;
    for(int i=0;i<m;i++){
        char u,v;
        int w;
        cin >> u >> v >> w;
        add_edge(enc(u),enc(v),w);
    }
    int ans=0;
    while(true){
        for(int i=0;i<N;i++){
            vis[i]=false;
        }
        int f=dfs(s,INT_MAX);
        if(f==0)break;
        ans+=f;
    }
    cout << ans << "\n";
}