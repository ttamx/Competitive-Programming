#include<bits/stdc++.h>

using namespace std;

const int N=100005;
const int M=100005;
const int Q=100005;
const int S=3420; // (2*N)^(2/3) = 3420
const int K=60; // (2*N)^(1/3) = 59
const int X=10'000'005;
const int B=3165; // sqrt(X) = 3163
const int BB=12; // 1 << 12 = 4096

int n,m,q;
vector<tuple<int,int,int>> adj[N];
int a[N],b[N],c[M],d[M],e[M];
int tin[N],tout[N],pos[2*N];
int timer=0;
int nxt[N],pre[N],last=0;

struct DS{
    int cnt[X],cnt2[((X-1)>>BB)+1];
    const int last=(X-1)>>BB;
    inline void update(int i,int v){
        cnt[i]+=v;
        cnt2[i>>BB]+=v;
    }
    inline int query(){
        for(int i=last;i>=0;i--){
            if(cnt2[i]>0){
                for(int j=min((i+1)<<BB,X)-1;;j--){
                    if(cnt[j]>0){
                        return j;
                    }
                }
            }
        }
        return 0;
    }
}ds;

struct Queries{
    int t,x,y;
}qr[Q];

struct MoAlgo{
    int ans[Q];
    int cnt[N],val[N];
    vector<tuple<int,int,int>> block[K][K];
    inline int insert(int l,int r,int i){
        block[(l-1)/S][(r-1)/S].emplace_back(i,l,r);
        return i;
    }
    inline void add(int i,int v){
        int u=pos[i];
        int col=a[u];
        ds.update(c[col]*val[col],-1);
        if(cnt[u]==1){
            val[col]-=b[u];
        }else{
            val[col]+=b[u];
        }
        cnt[u]+=v;
        ds.update(c[col]*val[col],+1);
    }
    inline void update(int i){
        int col=qr[i].x;
        ds.update(c[col]*val[col],-1);
        c[col]=qr[i].y;
        ds.update(c[col]*val[col],+1);
    }
    inline void undo(int i){
        int col=qr[i].x;
        ds.update(c[col]*val[col],-1);
        c[col]=d[i];
        ds.update(c[col]*val[col],+1);
    }
    inline void solve(){
        int st=1,ed=0,upd=0;
        for(int li=0;li<K;li++){
            for(int ri=li;ri<K;ri++){
                sort(block[li][ri].begin(),block[li][ri].end());
                for(auto [i,l,r]:block[li][ri]){
                    while(ed<r)add(++ed,+1);
                    while(st>l)add(--st,+1);
                    while(ed>r)add(ed--,-1);
                    while(st<l)add(st++,-1);
                    while(nxt[upd]<i){
                        update(upd=nxt[upd]);
                    }
                    while(upd>i){
                        undo(upd);
                        upd=pre[upd];
                    }
                    ans[i]=ds.query();
                }
            }
        }
    }
}mo;

void dfs(int u,int p=0){
    tin[u]=++timer;
    pos[timer]=u;
    for(auto [v,_a,_b]:adj[u]){
        if(v==p)continue;
        a[v]=_a,b[v]=_b;
        dfs(v,u);
    }
    tout[u]=++timer;
    pos[timer]=u;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<n;i++){
        int u,v,a,b;
        cin >> u >> v >> a >> b;
        adj[u].emplace_back(v,a,b);
        adj[v].emplace_back(u,a,b);
    }
    for(int i=1;i<=m;i++){
        cin >> c[i];
        e[i]=c[i];
    }
    dfs(1);
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> qr[i].t >> qr[i].x >> qr[i].y;
    }
    for(int i=1;i<=q;i++){
        if(qr[i].t==1){
            int u=qr[i].x,v=qr[i].y;
            if(tout[u]>tout[v])swap(u,v);
            mo.insert(tout[u],tout[v]-1,i);
        }else{
            pre[i]=last;
            nxt[last]=i;
            last=i;
            d[i]=e[qr[i].x];
            e[qr[i].x]=qr[i].y;
        }
    }
    nxt[last]=q+1;
    pre[q+1]=last;
    nxt[q+1]=q+1;
    ds.update(0,m+1);
    mo.solve();
    for(int i=1;i<=q;i++){
        if(qr[i].t==1){
            cout << mo.ans[i] << "\n";
        }
    }
}