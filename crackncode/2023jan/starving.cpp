#include<bits/stdc++.h>

using namespace std;

const bool DBG=false;
const int N=5e5+5;

int n,q,rt,lf;
int v[N],a[N],sz[N],lv[N],dist[N],pa[N][20],cp[N],b[N];
bool used[N];
vector<pair<int,int>> adj[N];

struct trio{
    int first,second,third;
};

multiset<pair<pair<int,int>,int>> ms[N];

struct node{
    int l,r,p;
}t[N];

void dfs(int u=1,int p=0){
    pa[u][0]=p;
    for(int i=1;i<20;i++)pa[u][i]=pa[pa[u][i-1]][i-1];
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        lv[v]=lv[u]+1;
        dist[v]=dist[u]+w;
        dfs(v,u);
    }
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

int calc(int a,int b){
    return dist[a]+dist[b]-2*dist[lca(a,b)];
}

int getsize(int u,int p=0){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=getsize(v,u);
    return sz[u];
}

int getcentroid(int u,int req,int p=0){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]*2>req)return getcentroid(v,req,u);
    return u;
}

void buildcentroid(int u=1,int p=0){
    u=getcentroid(u,getsize(u));
    used[u]=true;
    cp[u]=p;
    for(auto [v,w]:adj[u])if(!used[v])buildcentroid(v,u);
}

void updateup(int u,int val){
    if(DBG)cerr << "----------UPDATE----------\n";
    int v=u;
    while(v){
        int res=calc(u,v)+a[u];
        auto it=ms[v].lower_bound({{val,0},0});
        if(it!=ms[v].end()&&res>=it->first.second){
            v=cp[v];
            continue;
        }
        if(it!=ms[v].end()&&it->first.first==val)ms[v].erase(it);
        ms[v].insert({{val,res},u});
        it=ms[v].lower_bound({{val,0},0});
        while(it!=ms[v].begin()&&it->first.second<=prev(it)->first.second)ms[v].erase(prev(it));
        if(DBG){
            cerr << v << '\n';
            for(auto [x,y]:ms[v])cerr << "(" << x.first << "," << x.second << "," << y << ") ";
            cerr << '\n';
        }
        v=cp[v];
    }
}

int queryup(int u,int val){
    if(DBG)cerr << "----------QUERY----------\n";
    int res=2e9;
    int v=u;
    while(v){
        if(DBG){
            cerr << v << '\n';
            for(auto [x,y]:ms[v])cerr << "(" << x.first << "," << x.second << "," << y << ") ";
            cerr << '\n';
        }
        auto it=ms[v].lower_bound({{val,0},0});
        if(it!=ms[v].end()){
            if(DBG)cerr << "VAL : " << calc(it->second,u)+a[it->second] << '\n';
            res=min(res,calc(it->second,u)+a[it->second]);
        }
        v=cp[v];
    }
    if(DBG)cerr << "RETURN : " << res << '\n';
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> v[i];
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]=max(v[i]-2*a[i],0);
    }
    rt=1,lf=1;
    for(int i=2;i<=n;i++){
        while(lf&&v[i]>v[lf])lf=t[lf].p;
        if(lf==0){
            t[i].l=rt;
            t[rt].p=i;
            rt=i;
        }else{
            t[i].l=t[lf].r;
            t[t[lf].r].p=i;
            t[lf].r=i;
            t[i].p=lf;
        }
        lf=i;
    }
    for(int i=1;i<=n;i++){
        if(t[i].l)adj[i].emplace_back(t[i].l,v[i]-v[t[i].l]);
        if(t[i].r)adj[i].emplace_back(t[i].r,v[i]-v[t[i].r]);
        if(t[i].p)adj[i].emplace_back(t[i].p,v[t[i].p]-v[i]);
    }
    dfs();
    buildcentroid();
    while(q--){
        int o,x,y;
        cin >> o >> x >> y;
        if(o==1){
            b[x]+=y;
            updateup(x,b[x]);
        }else{
            int res=queryup(x,y);
            if(res==2e9){
                res=-1;
            }else{
                res=(res+v[x])/2;
            }
            cout << res << '\n';
        }
    }
}