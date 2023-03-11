#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<int,int,int> t3;

const int N=5e5+5;
const int K=1<<20;

int n,q,cnt;
int v[N],a[N];
int sz[N],cp[N],lv[N];
bool used[N];
vector<int> adj[N];
vector<pair<int,int>> dp[N];

struct node{
    int l,r,d;
    array<int,19> p;
}t[N];

void predfs(int u){
    t[u].d=t[t[u].p[0]].d+1;
    if(t[u].l)predfs(t[u].l);
    if(t[u].r)predfs(t[u].r);
}

int getlca(int a,int b){
    if(t[a].d<t[b].d)swap(a,b);
    for(int i=19;i>=0;i--)if(t[t[a].p[i]].d>=t[b].d)a=t[a].p[i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(t[a].p[i]!=t[b].p[i])a=t[a].p[i],b=t[b].p[i];
    return t[a].p[0];
}

int dfs(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
    return sz[u];
}

int getcentroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return getcentroid(v,cnt,u);
    return u;
}

void buildcentroid(int u=1,int p=0){
    u=getcentroid(u,dfs(u));
    cp[u]=p;
    used[u]=true;
    for(auto v:adj[u])if(!used[v])buildcentroid(v,u);
}

int centroidlca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    while(lv[a]>lv[b])a=cp[a];
    while(a!=b)a=cp[a],b=cp[b];
    return a;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> v[i];
    for(int i=1;i<=n;i++)cin >> a[i],a[i]=min(a[i],v[i]/2);
    int root=1,leaf=1;
    for(int i=2;i<=n;i++){
        while(leaf&&v[i]>v[leaf])leaf=t[leaf].p[0];
        if(leaf==0){
            t[i].l=root;
            t[root].p[0]=i;
            root=i;
        }else{
            t[i].l=t[leaf].r;
            t[t[leaf].r].p[0]=i;
            t[leaf].r=i;
            t[i].p[0]=leaf;
        }
        leaf=i;
    }
    predfs(root);
    for(int i=1;i<19;i++)for(int j=1;j<=n;j++)t[j].p[i]=t[t[j].p[i-1]].p[i-1];
    for(int i=1;i<=n;i++){
        if(t[i].l)adj[i].push_back(t[i].l);
        if(t[i].r)adj[i].push_back(t[i].r);
        if(t[i].p[0])adj[i].push_back(t[i].p[0]);
    }
    buildcentroid();
    for(int i=1;i<=n;i++){
        int u=i;
        while(u){
            lv[i]++;
            dp[i].push_back({u,2e9});
            u=cp[u];
        }
    }
    while(q--){
        int o,x,y;
        cin >> o >> x >> y;
        if(o==1){
            int lca=centroidlca(x,root);
            for(auto &[u,w]:dp[x])if(getlca(u,x)==u)w=min(w,min(v[u],v[x])-a[x]);
            for(auto &[u,w]:dp[root])if(getlca(u,x)==u)w=min(w,min(v[u],v[root])-a[x]);
        }else{
            int lca=centroidlca(x,root);
            int ans=2e9;
            for(auto &[u,w]:dp[x])if(u==lca)ans=min(ans,w);
            for(auto &[u,w]:dp[root])if(u==lca)ans=min(ans,w);
            if(ans>1e9)ans=-1;
            cout << ans << '\n';
        }
    }
}