#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=11;
const int LG=17;
const int INF=1e9;

int n,m,k,q;
vector<int> adj[N],adj2[N],up[N];
int par[N],dep[N],sz[N],bel[N];
int dist[LG][K][N],dist2[N][K];
bool used[N];
int buf=0;

void dfs(int u,int p){
    par[u]=p;
    dep[u]=dep[p]+1;
    up[u].emplace_back(u);
    for(auto v:adj2[u]){
        if(v==p)continue;
        if(!dep[v]){
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
            dfs(v,u);
        }else if(dep[v]<dep[u]){
            for(int x=u;x!=v;x=par[x])up[x].emplace_back(v);
        }
    }
}

int dfs_sz(int u,int p){
    sz[u]=1;
    bel[u]=buf;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs_sz(v,u);
    return sz[u];
}

int centroid(int u,int p,int cnt){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,u,cnt);
    return u;
}

void decom(int u,int p){
    buf++;
    u=centroid(u,0,dfs_sz(u,0));
    par[u]=p;
    dep[u]=dep[p]+1;
    for(int i=0;i<up[u].size();i++){
        int v=up[u][i];
        if(bel[v]!=buf)continue;
        int *d=dist[dep[u]][i];
        queue<int> q;
        d[v]=0;
        q.emplace(v);
        while(!q.empty()){
            auto x=q.front();
            q.pop();
            for(auto y:adj2[x]){
                if(bel[y]==buf&&d[x]+1<d[y]){
                    d[y]=d[x]+1;
                    q.emplace(y);
                }
            }
        }
    }
    used[u]=true;
    for(auto v:adj[u])if(!used[v])decom(v,u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj2[u].emplace_back(v);
        adj2[v].emplace_back(u);
    }
    for(int i=0;i<LG;i++){
        for(int j=0;j<K;j++){
            for(int u=1;u<=n;u++){
                dist[i][j][u]=INF;
            }
        }
    }
    for(int u=1;u<=n;u++){
        for(int i=0;i<K;i++){
            dist2[u][i]=INF;
        }
    }
    dfs(1,0);
    dep[0]=-1;
    decom(1,0);
    cin >> q;
    while(q--){
        int op,u;
        cin >> op >> u;
        int res=INF;
        for(int v=u;v!=0;v=par[v]){
            for(int i=0;i<up[v].size();i++){
                if(op==1){
                    dist2[v][i]=min(dist2[v][i],dist[dep[v]][i][u]);
                }else{
                    res=min(res,dist[dep[v]][i][u]+dist2[v][i]);
                }
            }
        }
        if(op==2){
            cout << res << "\n";
        }
    }
}