#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
vector<int> adj[N];
int lv[N],pa[N][20];

void dfs(int u,int p){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u])dfs(v,u);
}

int lca(int u,int v){
    if(lv[u]<lv[v])swap(u,v);
    for(int i=19;i>=0;i--)if(lv[pa[u][i]]>=lv[v])u=pa[u][i];
    if(u==v)return u;
    for(int i=19;i>=0;i--)if(pa[u][i]!=pa[v][i])u=pa[u][i],v=pa[v][i];
    return pa[u][0];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        while(x--){
            int y;
            cin >> y;
            adj[i].emplace_back(y);
        }
    }
    dfs(0,0);
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        cout << lca(u,v) << "\n";
    }
}