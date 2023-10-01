#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int inf=1e9;

int n;
int w[N];
int pa[20][N],lv[N];
vector<int> adj[N];

struct node{
    int mn,mx,mnp,mns,mxp,mxs,all;
    node(int x=0):mn(min(x,0)),mx(max(x,0)),mnp(min(x,0)),mns(min(x,0)),mxp(max(x,0)),mxs(max(x,0)),all(x){}
    friend node operator+(node a,node b){
        node c;
        c.mn=min({a.mn,b.mn,a.mns+b.mnp});
        c.mx=max({a.mx,b.mx,a.mxs+b.mxp});
        c.mnp=min(a.mnp,a.all+b.mnp);
        c.mns=min(a.mns+b.all,b.mns);
        c.mxp=max(a.mxp,a.all+b.mxp);
        c.mxs=max(a.mxs+b.all,b.mxs);
        c.all=a.all+b.all;
        return c;
    }
    node rev(){
        node x=*this;
        swap(x.mnp,x.mns);
        swap(x.mxp,x.mxs);
        return x;
    }
}dp[20][N];

void dfs(int u,int p=0){
    lv[u]=lv[p]+1;
    pa[0][u]=p;
    dp[0][u]=w[u];
    for(int i=1;i<20;i++){
        pa[i][u]=pa[i-1][pa[i-1][u]];
        dp[i][u]=dp[i-1][pa[i-1][u]]+dp[i-1][u];
    }
    for(auto v:adj[u])dfs(v,u);
}

node lca(int u,int v){
    if(lv[u]<lv[v])swap(u,v);
    node resl,resr;
    for(int i=19;i>=0;i--){
        if(lv[pa[i][u]]<lv[v])continue;
        resl=dp[i][u]+resl;
        u=pa[i][u];
    }
    if(u==v)return dp[0][u]+resl;
    for(int i=19;i>=0;i--){
        if(pa[i][u]==pa[i][v])continue;
        resl=dp[i][u]+resl;
        resr=dp[i][v]+resr;
        u=pa[i][u];
        v=pa[i][v];
    }
    resl=dp[1][u]+resl;
    resr=dp[0][v]+resr;
    return resr.rev()+resl;
}

void runcase(){
    cin >> n;
    int idx=1;
    vector<tuple<int,int,int>> qr;
    for(int i=1;i<=n;i++){
        char c;
        cin >> c;
        if(c=='+'){
            idx++;
            int u;
            cin >> u >> w[idx];
            adj[u].emplace_back(idx);
        }else{
            int u,v,k;
            cin >> u >> v >> k;
            qr.emplace_back(u,v,k);
        }
    }
    w[1]=1;
    dfs(1);
    for(auto [u,v,k]:qr){
        node x=lca(u,v);
        cout << ((x.mn<=k&&k<=x.mx)?"YES":"NO") << "\n";
    }
    for(int i=1;i<=idx;i++)adj[i].clear();
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}