#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const bool DBG=false;
const int N=2e5+5;

int n,l,r;
int sz[N],lv[N],cp[N];
int pa[N][20];
bool used[N];
vector<int> adj[N],cadj[N],ch[N];
ll ans;

struct fenwick{
    int t[N];
    void add(int i,int v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    int read(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

void init(){
    ans=0;
    for(int i=1;i<=n;i++){
        adj[i].clear();
        cadj[i].clear();
        used[i]=false;
        ch[i].clear();
    }
}

void predfs(int u=1,int p=0){
    lv[u]=lv[p]+1;
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto v:adj[u]){
        if(v==p)continue;
        predfs(v,u);
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int dist(int a,int b){
    return lv[a]+lv[b]-2*lv[lca(a,b)];
}

int dfs(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u]){
        if(used[v]||v==p)continue;
        sz[u]+=dfs(v,u);
    }
    return sz[u];
}

int getcentroid(int u,int req,int p=0){
    for(auto v:adj[u])if(!used[v]&&v!=p&&sz[v]*2>req)return getcentroid(v,req,u);
    return u;
}

void buildcentroid(int u=1,int p=0){
    u=getcentroid(u,dfs(u));
    cp[u]=p;
    cadj[p].push_back(u);
    used[u]=true;
    for(auto v:adj[u])if(!used[v])buildcentroid(v,u);
}

void updateup(int u){
    int v=u;
    while(v){
        ch[v].push_back(u);
        v=cp[v];
    }
}

void runcase(){
    cin >> n >> l >> r;
    l=n-1-l;
    r=n-1-r;
    swap(l,r);
    init();
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    predfs();
    buildcentroid();
    for(int i=1;i<=n;i++)updateup(i);
    for(int u=1;u<=n;u++){
        if(DBG)cerr << u << " : ";
        for(auto v:cadj[u]){
            if(DBG)cerr << v << ' ';
            for(auto w:ch[v])ans+=f.read(r-dist(u,w))-f.read(l-dist(u,w)-1);
            for(auto w:ch[v])f.add(dist(w,u),1);
        }
        if(DBG)cerr << '\n';
        ans+=f.read(r)-f.read(l-1);
        for(auto v:cadj[u]){
            for(auto w:ch[v])f.add(dist(w,u),-1);
        }
    }
    if(DBG)cerr << "----------------\n";
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    if(!DBG)freopen("awesome.in","r",stdin);
    int t(1);
    cin >> t;
    while(t--)runcase();
}