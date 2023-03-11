#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;

int n,m,t,d,idx;
vector<pair<int,int>> edge,edge2;
vector<int> adj[N],adj2[N],rev[N],rev2[N];
stack<int> s;
bool vis[N];
int deg[N],mp[N];

void dfs(int u){
    if(vis[u])return;
    vis[u]=true;
    for(auto v:adj[u])dfs(v);
    for(auto v:adj2[u])dfs(v);
    s.push(u);
}

void kos(int u){
    if(vis[u])return;
    vis[u]=true;
    mp[u]=idx;
    for(auto v:rev[u])kos(v);
    for(auto v:rev2[u])kos(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> t >> d;
    d++;
    edge.resize(m);
    edge2.resize(t);
    for(auto &[u,v]:edge){
        cin >> u >> v;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for(auto &[u,v]:edge2)cin >> u >> v;
    int l=0,r=t+1;
    while(l<r){
        int mid=(l+r)/2;
        for(int i=1;i<=n;i++){
            deg[i]=0;
            vis[i]=false;
            adj2[i].clear();
            rev2[i].clear();
        }
        for(int i=0;i<mid;i++){
            auto [u,v]=edge2[i];
            adj2[u].push_back(v);
            rev2[v].push_back(u);
        }
        for(int i=1;i<=n;i++)dfs(i);
        for(int i=1;i<=n;i++)vis[i]=false;
        idx=0;
        while(!s.empty()){
            int u=s.top();
            s.pop();
            if(vis[u])continue;
            idx++;
            kos(u);
        }
        for(auto [u,v]:edge)if(mp[u]!=mp[v])deg[mp[v]]++;
        for(int i=0;i<mid;i++){
            auto [u,v]=edge2[i];
            if(mp[u]!=mp[v])deg[mp[v]]++;
        }
        int cnt=0;
        for(int i=1;i<=idx;i++)if(deg[i]==0)cnt++;
        if(cnt<=d)r=mid;
        else l=mid+1;
    }
    cout << (l<=t?l:-1);
}