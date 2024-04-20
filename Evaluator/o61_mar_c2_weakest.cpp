#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

const int N=1e5+5;
const int K=20;

int n,q,k,m;
vector<pair<int,int>> adj[N];
int w[N],a[N];
int lv[N],pa[K][N],mn[K][N];

void dfs(int u){
    for(auto [v,w]:adj[u]){
        lv[v]=lv[u]+1;
        pa[0][v]=u;
        mn[0][v]=w;
        for(int i=1;i<K;i++){
            pa[i][v]=pa[i-1][pa[i-1][v]];
            mn[i][v]=min(mn[i-1][v],mn[i-1][pa[i-1][v]]);
        }
        dfs(v);
    }
}

int lca(int u,int v){
    int res=INF;
    if(lv[u]<lv[v])swap(u,v);
    for(int i=K-1;i>=0;i--)if(lv[pa[i][u]]>=lv[v]){
        res=min(res,mn[i][u]);
        u=pa[i][u];
    }
    if(u==v)return res;
    for(int i=K-1;i>=0;i--)if(pa[i][u]!=pa[i][v]){
        res=min(res,mn[i][u]);
        res=min(res,mn[i][v]);
        u=pa[i][u];
        v=pa[i][v];
    }
    res=min(res,mn[0][u]);
    res=min(res,mn[0][v]);
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int p,w;
        cin >> p >> w;
        adj[p].emplace_back(i,w);
    }
    for(int i=0;i<K;i++)for(int j=0;j<n;j++)mn[i][j]=INF;
    dfs(0);
    cin >> q >> k >> m >> a[1] >> a[2];
    for(int i=1;i<=q;i++){
        int ans=a[i]==a[i+1]?0:lca(a[i],a[i+1]);
        a[i+2]=(1ll*a[i+1]*k+ans)%m%n;
        cout << ans << "\n";
    }
}