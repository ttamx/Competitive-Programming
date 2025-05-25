#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<int> p(n),deg(n);
    vector<vector<int>> adj(n);
    for(auto &x:p)cin >> x,x--;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[v].emplace_back(u);
        deg[u]++;
    }
    vector<int> ord;
    for(int i=0;i<n;i++)if(!deg[i])ord.emplace_back(i);
    for(int i=0;i<ord.size();i++){
        int u=ord[i];
        for(auto v:adj[u])if(!(--deg[v]))ord.emplace_back(v);
    }
    assert(ord.size()==n);
    for(auto u:ord)for(auto v:adj[u])p[v]=min(p[v],p[u]-1);
    for(int i=0;i<n;i++){
        vector<bool> vis(n);
        vis[i]=true;
        int cnt=0;
        for(auto u:ord){
            if(!vis[u])continue;
            cnt++;
            for(auto v:adj[u])vis[v]=true;
        }
        cnt--;
        vector<int> c(n);
        for(int j=0;j<n;j++)if(!vis[j])c[p[j]]++;
        for(int j=n-1;j>cnt;j--){
            c[j-1]+=max(c[j]-1,0);
            if(!c[j]){
                cnt=j;
                break;
            }
        }
        cout << cnt+1 << " ";
    }
}