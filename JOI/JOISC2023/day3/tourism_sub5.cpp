#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;
const int S=350;

typedef long long ll;

int n,m,q,sq;
int c[N];
int sz[N],heavy[N],chain[N],head[N],pos[N],chainid,posid;
int lv[N],pa[N][20];
vector<int> adj[N];
pair<int,int> qr[N];
int ans[N];
int cnt[N];
int LCA[N];
int res=0;
vector<int> vec[S];

void dfs(int u,int p){
    sz[u]=1;
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[heavy[u]])heavy[u]=v;
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

void add(int u,int v,int i){
    int LCA=lca(u,v);
    while(u!=LCA){
        cnt[u]++;
        if(cnt[u]==1)res++;
        u=pa[u][0];
    }
    while(v!=LCA){
        cnt[v]++;
        if(cnt[v]==1)res++;
        v=pa[v][0];
    }
}

void del(int u,int v,int i){
    while(u!=LCA[i]){
        cnt[u]--;
        if(cnt[u]==0)res--;
        u=pa[u][0];
    }
    while(v!=LCA[i]){
        cnt[v]--;
        if(cnt[v]==0)res--;
        v=pa[v][0];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    sq=320;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    head[++chainid]=1;
    for(int i=1;i<=m;i++)cin >> c[i];
    for(int i=1;i<=q;i++){
        auto &[l,r]=qr[i];
        cin >> l >> r;
        vec[l/sq].emplace_back(i);
    }
    for(int i=2;i<=m;i++)LCA[i]=lca(c[i],c[i-1]);
    int st=1,ed=1;
    for(int i=0;i<=sq;i++){
        sort(vec[i].begin(),vec[i].end(),[&](int x,int y){
            return qr[x].second<qr[y].second;
        });
        for(auto j:vec[i]){
            auto [l,r]=qr[j];
            while(st>l){
                add(c[st-1],c[st],st);
                st--;
            }
            while(ed<r){
                add(c[ed],c[ed+1],ed+1);
                ed++;
            }
            while(st<l){
                del(c[st],c[st+1],st+1);
                st++;
            }
            while(ed>r){
                del(c[ed-1],c[ed],ed);
                ed--;
            }
            ans[j]=res+1;
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i] << '\n';
}