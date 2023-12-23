#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

const int N=2e5+5;

int n,m,cn;
vi tadj[N],adj[9*N];
int lv[N],pa[N],hv[N],sz[N],hd[N],pos[N],id[N];
int in[4*N],out[4*N];
int deg[9*N],ans[N];
int timer;

void link(int u,int v){
    adj[u].emplace_back(v);
    deg[v]++;
}

void dfs(int u,int p=0){
    sz[u]=1;
    pa[u]=p;
    lv[u]=lv[p]+1;
    for(auto v:tadj[u])if(v!=p){
        dfs(v,u);
        sz[u]+=sz[v];
        if(sz[v]>sz[hv[u]])hv[u]=v;
    }
}

void hld(int u,int p=0){
    pos[u]=++timer;
    id[timer]=u;
    if(hv[u])hd[hv[u]]=hd[u],hld(hv[u],u);
    for(auto v:tadj[u])if(v!=p&&v!=hv[u])hd[v]=v,hld(v,u);
}

vector<pii> getpath(int u,int v){
    vector<pii> res;
    while(hd[u]!=hd[v]){
        if(lv[hd[u]]<lv[hd[v]])swap(u,v);
        res.emplace_back(pos[u],pos[hd[u]]);
        u=pa[hd[u]];
    }
    if(lv[u]<lv[v])swap(u,v);
    res.emplace_back(pos[u],pos[v]);
    return res;
}

void build(int l,int r,int i){
    if(l==r)return void(in[i]=out[i]=id[l]);
    int m=(l+r)/2;
    build(l,m,i*2);
    build(m+1,r,i*2+1);
    in[i]=++cn,out[i]=++cn;
    link(in[i],in[i*2]);
    link(in[i],in[i*2+1]);
    link(out[i*2],out[i]);
    link(out[i*2+1],out[i]);
}

void addin(int l,int r,int i,int x,int y,int u){
    if(y<l||r<x)return;
    if(x<=l&&r<=y)return link(u,in[i]);
    int m=(l+r)/2;
    addin(l,m,i*2,x,y,u);
    addin(m+1,r,i*2+1,x,y,u);
}

void addout(int l,int r,int i,int x,int y,int u){
    if(y<l||r<x)return;
    if(x<=l&&r<=y)return link(out[i],u);
    int m=(l+r)/2;
    addout(l,m,i*2,x,y,u);
    addout(m+1,r,i*2+1,x,y,u);
}

void add(int l,int r,int c,int t){
    if(t==1)addin(1,n,1,l,r,c);
    else addout(1,n,1,l,r,c);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
     for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        tadj[u].emplace_back(v);
        tadj[v].emplace_back(u);
    }
    cn=n;
    dfs(1),hd[1]=1,hld(1);
    build(1,n,1);
    for(int i=0;i<m;i++){
        int t,a,b,c;
        cin >> t >> a >> b >> c;
        auto path=getpath(a,b);
        for(auto [l,r]:path){
            if(l>r)swap(l,r);
            if(l<=pos[c]&&pos[c]<=r){
                if(l<pos[c])add(l,pos[c]-1,c,t);
                if(pos[c]<r)add(pos[c]+1,r,c,t);
            }else{
                add(l,r,c,t);
            }
        }
    }
    queue<int> q;
    int cnt=0;
    for(int i=1;i<=cn;i++)if(deg[i]==0)q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        if(u<=n)ans[u]=++cnt;
        for(auto v:adj[u])if(--deg[v]==0)q.emplace(v);
    }
    if(cnt<n)cout << -1;
    else for(int i=1;i<=n;i++)cout << ans[i] << " ";
}