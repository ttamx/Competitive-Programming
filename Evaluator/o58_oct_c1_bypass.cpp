#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
long long ans;
int ch[N],pa[N],mx1[N],mx2[N];
vector<int> adj[N];
vector<pair<int,int>> edge;

void dfs(int u,int p){
    pa[u]=p;
    ch[u]=1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        ch[u]+=ch[v];
        if(ch[v]>mx1[u]){
            mx2[u]=mx1[u];
            mx1[u]=ch[v];
        }else if(ch[v]>mx2[u]){
            mx2[u]=ch[v];
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    edge.resize(n-1);
    for(auto &[u,v]:edge){
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    for(auto [u,v]:edge){
        if(pa[u]==v)swap(u,v);
        int c1=mx1[u];
        if(c1==ch[v])c1=mx2[u];
        c1=max(c1,n-ch[u]);
        int c2=mx1[v];
        ans=max(ans,1ll*c1*c2);
    }
    cout << ans;
}