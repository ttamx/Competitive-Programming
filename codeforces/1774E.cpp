#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,d,ans;
int q1,q2;
bool vis1[N],vis2[N];
int pa[N][20],lv[N];
vector<int> adj[N];

void dfs(int u,int p,int l){
    pa[u][0]=p;
    lv[u]=l;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u])if(v!=p)dfs(v,u,l+1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> d;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,1,0);
    vis1[1]=vis2[1]=true;
    vector<int> Q1;
    vector<int> Q2;
    cin >> q1;
    for(int i=0;i<q1;i++){
        int u;
        cin >> u;
        Q1.push_back(u);
        int v=u;
        int dist=d;
        for(int i=19;i>=0;i--){
            if(dist>=(1<<i)){
                dist-=(1<<i);
                v=pa[v][i];
            }
        }
        Q2.push_back(v);
    }
    cin >> q2;
    for(int i=0;i<q2;i++){
        int u;
        cin >> u;
        Q2.push_back(u);
        int v=u;
        int dist=d;
        for(int i=19;i>=0;i--){
            if(dist>=(1<<i)){
                dist-=(1<<i);
                v=pa[v][i];
            }
        }
        Q1.push_back(v);
    }
    for(auto u:Q1){
        while(!vis1[u]){
            vis1[u]=true;
            ans+=2;
            u=pa[u][0];
        }
    }
    for(auto u:Q2){
        while(!vis2[u]){
            vis2[u]=true;
            ans+=2;
            u=pa[u][0];
        }
    }
    cout << ans;
}