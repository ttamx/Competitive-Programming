#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int n,m,k;
vector<int> adj[N];
int match[N];
bool vis[N];
int ans=0;

bool kuhn(int u){
    if(vis[u])return false;
    vis[u]=true;
    for(auto v:adj[u]){
        if(!match[v]||kuhn(match[v])){
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<k;i++){
        int u,v;
        cin >> u >> v;
        v+=n;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!match[i]&&kuhn(i)){
            ans++;
            for(int j=1;j<=n+m;j++){
                vis[j]=false;
            }
        }
    }
    cout << ans << "\n";
    for(int i=1;i<=n;i++){
        if(match[i]){
            cout << i << " " << match[i]-n << "\n";
        }
    }
}