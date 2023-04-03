#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,cnt;
int ans[N],lv[N];
bool vis[N];
vector<int> q;
vector<int> adj[N];

void dfs(int u,int p=0){
    lv[u]=lv[p]+1;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cnt=n+1;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    int idx=1;
    for(int i=1;i<=n;i++)if(lv[i]>lv[idx])idx=i;
    dfs(idx);
    if(!vis[idx])q.emplace_back(idx);
    vis[idx]=true;
    for(int i=1;i<=n;i++)if(lv[i]>lv[idx])idx=i;
    for(int i=1;i<=n;i++)if(lv[i]==lv[idx]){
        if(!vis[i])q.emplace_back(i);
        vis[i]=true;
    }
    dfs(idx);
    if(!vis[idx])q.emplace_back(idx);
    vis[idx]=true;
    for(int i=1;i<=n;i++)if(lv[i]>lv[idx])idx=i;
    for(int i=1;i<=n;i++)if(lv[i]==lv[idx]){
        if(!vis[i])q.emplace_back(i);
        vis[i]=true;
    }
    for(auto x:q)vis[x]=true;
    for(int i=n;i>=1;i--){
        if(i>lv[idx]-1){
            ans[i]=n;
            continue;
        }
        vector<int> res;
        for(auto u:q){
            cnt--;
            for(auto v:adj[u]){
                if(vis[v])continue;
                vis[v]=true;
                res.emplace_back(v);
            }
        }
        q=res;
        ans[i]=max(1,cnt);
    }
    for(int i=1;i<=n;i++)cout << ans[i] << ' ';
}