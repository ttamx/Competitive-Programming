#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,k;
vector<int> adj[N];
int ans=1;

int dfs(int u,int p){
    vector<int> a;
    for(auto v:adj[u])if(v!=p){
        a.emplace_back(dfs(v,u));
    }
    if(a.empty())return 1;
    sort(a.rbegin(),a.rend());
    int c=a[0];
    for(int i=1;i<a.size();i++)if(c+a[i]>k)c=a[i],ans++;
    return c+1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)if(adj[i].size()>1){
        dfs(i,0);
        break;
    }
    cout << ans << "\n";
}