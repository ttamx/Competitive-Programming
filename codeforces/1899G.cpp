#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct fenwick{
    int t[N];
    int n;
    void init(int _n){
        n=_n;
        for(int i=1;i<=n;i++)t[i]=0;
    }
    void add(int i,int v){
        while(i<=n)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

void runcase(){
    int n,q;
    cin >> n >> q;
    f.init(n);
    vector<vector<int>> adj(n+2);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> a(n+2);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        a[x]=i;
    }
    vector<vector<tuple<int,int,int>>> qr(n+2);
    vector<bool> ans(q);
    for(int i=0;i<q;i++){
        int l,r,x;
        cin >> l >> r >> x;
        qr[x].emplace_back(l,r,i);
    }
    vector<int> sz(n+2),hv(n+2),tin(n+2),tout(n+2),pos(n+2);
    int timer=0;
    function<int(int,int)> dfssz=[&](int u,int p){
        tin[u]=++timer;
        pos[timer]=u;
        sz[u]=1;
        for(auto v:adj[u])if(v!=p){
            sz[u]+=dfssz(v,u);
            if(sz[v]>sz[hv[u]])hv[u]=v;
        }
        tout[u]=timer;
        return sz[u];
    };
    dfssz(1,0);
    function<void(int,int,int)> dfs=[&](int u,int p,bool del){
        for(auto v:adj[u])if(v!=p&&v!=hv[u])dfs(v,u,true);
        if(hv[u])dfs(hv[u],u,false);
        f.add(a[u],1);
        for(auto v:adj[u])if(v!=p&&v!=hv[u])for(int i=tin[v];i<=tout[v];i++)f.add(a[pos[i]],1);
        for(auto [l,r,i]:qr[u])ans[i]=f.read(r)-f.read(l-1)>0;
        if(del)for(int i=tin[u];i<=tout[u];i++)f.add(a[pos[i]],-1);
    };
    dfs(1,0,true);
    for(auto x:ans)cout << (x?"YES":"NO") << "\n";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}