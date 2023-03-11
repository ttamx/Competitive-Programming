#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,r;
    cin >> n >> r;
    r--;
    vector<int> c(n-1);
    for(auto &x:c)cin >> x,x--;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> sz(n),lv(n),cp(n);
    vector<bool> used(n);
    vector<array<int,20>> pa(n);
    function<void(int,int)> predfs=[&](int u,int p){
        lv[u]=lv[p]+1;
        pa[u][0]=p;
        for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
        for(auto v:adj[u])if(v!=p)predfs(v,u);
    };
    auto lca=[&](int a,int b){
        if(lv[a]<lv[b])swap(a,b);
        for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
        if(a==b)return a;
        for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
        return pa[a][0];
    };
    auto dist=[&](int a,int b){
        return lv[a]+lv[b]-2*lv[lca(a,b)];
    };
    function<int(int,int)> dfs=[&](int u,int p){
        sz[u]=1;
        for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
        return sz[u];
    };
    function<int(int,int,int)> getcentroid=[&](int u,int p,int req){
        for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>req)return getcentroid(v,u,req);
        return u;
    };
    function<void(int,int)> buildcentroid=[&](int u,int p){
        u=getcentroid(u,u,dfs(u,-1));
        cp[u]=p;
        used[u]=true;
        for(auto v:adj[u])if(!used[v])buildcentroid(v,u);
    };
    predfs(r,r);
    buildcentroid(r,-1);
    int ans=n-1;
    vector<pair<int,int>> mn(n,{n-1,r});
    int u=r;
    while(u!=-1){
        mn[u]={dist(u,r),r};
        u=cp[u];
    }
    for(auto x:c){
        u=x;
        while(u!=-1){
            ans=min(ans,dist(x,mn[u].second));
            int d=dist(x,u);
            if(d<mn[u].first)mn[u]={d,x};
            u=cp[u];
        }
        cout << ans << ' ';
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}