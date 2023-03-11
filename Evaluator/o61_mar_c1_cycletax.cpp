#include<bits/stdc++.h>

using namespace std;

const int N=1005;
const int M=10005;

int n,m,cnt;
int u[M],v[M],deg[N];
int disc[N];
bool vis[N],used[M];
vector<pair<int,int>> adj[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    int mn=2e9,idx;
    for(int i=1;i<=m;i++){
        int w;
        cin >> u[i] >> v[i] >> w;
        adj[u[i]].emplace_back(v[i],i);
        adj[v[i]].emplace_back(u[i],i);
        if(w<mn){
            mn=w;
            idx=i;
        }
    }
    cout << mn << ' ' << 1 << '\n';
    cout << v[idx] << ' ' << u[idx] << ' ' << 1 << '\n';
    queue<int> q;
    q.emplace(v[idx]);
    vis[u[idx]]=true;
    vis[v[idx]]=true;
    while(!q.empty()){
        int cur=q.front();
        q.pop();
        disc[cur]=--cnt;
        for(auto [to,i]:adj[cur]){
            if(vis[to])continue;
            vis[to]=true;
            q.emplace(to);
        }
    }
    disc[u[idx]]=--cnt;
    for(int i=1;i<=m;i++){
        if(i==idx)continue;
        if(disc[u[i]]>disc[v[i]])swap(u[i],v[i]);
        cout << u[i] << ' ' << v[i] << ' ' << 0 << '\n';
    }
}