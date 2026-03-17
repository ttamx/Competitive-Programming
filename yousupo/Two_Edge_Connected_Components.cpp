#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,m,timer,top,cnt;
basic_string<int> adj[N],comp[N];
int disc[N],low[N],st[N];

void tarj(int u,int p){
    int f=0;disc[u]=low[u]=++timer,st[++top]=u;
    for(auto v:adj[u]){
        if(v==p&&!(f++))continue;
        if(!disc[v])tarj(v,u),low[u]=min(low[u],low[v]);
        else low[u]=min(low[u],disc[v]);
    }
    if(low[u]==disc[u]){
        do comp[cnt]+=st[top];while(st[top--]!=u);
        cnt++;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0,u,v;i<m;i++)cin >> u >> v,adj[u]+=v,adj[v]+=u;
    for(int i=0;i<n;i++)if(!disc[i])tarj(i,-1);
    cout << cnt << "\n";
    for(int i=0;i<cnt;i++){
        cout << comp[i].size();
        for(auto x:comp[i])cout << " " << x;
        cout << "\n";
    }
}