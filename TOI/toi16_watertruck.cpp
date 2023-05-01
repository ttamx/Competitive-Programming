#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,ans,ti,res;
int eu[N],ev[N],ew[N];
int disc[N],low[N],scc[N];
int path[N];
bool used[N],vis[N];
vector<int> adj[N],adj2[N];

int go(int u,int i){
    return u^eu[i]^ev[i];
}

void tarj(int u,int p=-1){
    disc[u]=low[u]=++ti;
    for(auto i:adj[u]){
        int v=go(u,i);
        if(!disc[v]){
            tarj(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>disc[u]){
                ans+=2*ew[i];
                used[i]=true;
            }
        }else if(v!=p){
            low[u]=min(low[u],disc[v]);
        }
    }
}

int pre(int u,int p=-1){
    if(vis[u])return 0;
    vis[u]=true;
    int res=0;
    for(auto i:adj2[u]){
        int v=go(u,i);
        if(v==p)continue;
        res+=1+pre(v,u);
    }
    return res;
}

void dfs(int u,int cnt,int dist,int st){
    if(dist>=res)return;
    if(cnt==0&&u==st)return void(res=dist);
    for(auto i:adj2[u]){
        if(path[i]==2)continue;
        int v=go(u,i);
        path[i]++;
        dfs(v,cnt-(path[i]==1),dist+ew[i],st);
        path[i]--;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        cin >> eu[i] >> ev[i] >> ew[i];
        adj[eu[i]].emplace_back(i);
        adj[ev[i]].emplace_back(i);
    }
    tarj(0);
    for(int i=1;i<=m;i++){
        if(used[i])continue;
        adj2[eu[i]].emplace_back(i);
        adj2[ev[i]].emplace_back(i);
    }
    for(int i=0;i<n;i++){
        int cnt=pre(i);
        cerr << i << ' ' << cnt << '\n';
        if(!cnt)continue;
        res=2e9;
        dfs(i,cnt,0,i);
        cerr << i << ' ' << res << '\n';
    }
    cout << ans;
}