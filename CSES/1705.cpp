#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int M=2e5+5;

int n,m,q;
vector<int> adj[N],adj2[M];
int disc[N],low[N],id[N];
int timer,cnt,nid;
stack<int> s;
vector<int> comp[M];
bool isap[N];
int sz[M],hv[M],lv[M],hd[M],pa[M],tin[M],tout[M];

void tarj(int u,int p=0){
    disc[u]=low[u]=++timer;
    s.emplace(u);
    for(auto v:adj[u])if(v!=p){
        if(disc[v]){
            low[u]=min(low[u],disc[v]);
        }else{
            tarj(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=disc[u]){
                isap[u]|=(disc[u]>1||disc[v]>2);
                comp[++cnt].emplace_back(u);
                while(comp[cnt].back()!=v){
                    comp[cnt].emplace_back(s.top());
                    s.pop();
                }
            }
        }
    }
}

void dfs(int u,int p=0){
    tin[u]=++timer;
    pa[u]=p;
    sz[u]=1;
    for(auto v:adj2[u])if(v!=p){
        lv[v]=lv[u]+1;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
    tout[u]=timer;
}

void hld(int u,int p=0){
    if(!hd[u])hd[u]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:adj2[u])if(v!=p&&v!=hv[u])hld(v,u);
}

int lca(int u,int v){
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        u=pa[hd[u]];
    }
    return lv[u]<lv[v]?u:v;
}

bool is_ancestor(int u,int p){
    return tin[p]<=tin[u]&&tout[u]<=tout[p];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    tarj(1);
    for(int i=1;i<=n;i++)if(isap[i])id[i]=++nid;
    for(int i=1;i<=cnt;i++){
        ++nid;
        for(auto u:comp[i]){
            if(isap[u]){
                adj2[nid].emplace_back(id[u]);
                adj2[id[u]].emplace_back(nid);
            }else{
                id[u]=nid;
            }
        }
    }
    timer=0;
    dfs(1);
    hld(1);
    while(q--){
        int u,v,p;
        cin >> u >> v >> p;
        if(u==p||v==p){
            cout << "NO\n";
            continue;
        }
        if(!isap[p]){
            cout << "YES\n";
            continue;
        }
        u=id[u],v=id[v],p=id[p];
        int x=lca(u,v);
        cout << ((is_ancestor(p,x)&&(is_ancestor(u,p)||is_ancestor(v,p)))?"NO":"YES") << "\n";
    }
}