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
vector<int> vec[S];

struct segtree{
    ll sum[K],cnt[K],lzsum[K],lzcnt[K];
    void build(int l,int r,int i){
        sum[i]=0;
        cnt[i]=0;
        lzsum[i]=0;
        lzcnt[i]=-1;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void pushlzcnt(int l,int r,int i){
        if(lzcnt[i]==-1)return;
        cnt[i]=(r-l+1)*lzcnt[i];
        cerr << "CNT1 : " << l << " " << r << " = " << cnt[i] << "\n";
        if(l<r){
            lzcnt[i*2]=lzcnt[i];
            lzcnt[i*2+1]=lzcnt[i];
        }
        lzcnt[i]=-1;
    }
    void pushlzsum(int l,int r,int i){
        if(lzsum[i]==0)return;
        sum[i]+=(r-l+1)*lzsum[i];
        if(l<r){
            lzsum[i*2]+=lzsum[i];
            lzsum[i*2+1]+=lzsum[i];
        }
        lzsum[i]=0;
        if(sum[i]==0){
            lzcnt[i]=0;
            pushlzcnt(l,r,i);
        }
    }
    void updatecnt(int l,int r,int i,int x,int y,ll v){
        pushlzsum(l,r,i);
        pushlzcnt(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            lzcnt[i]=v;
            pushlzcnt(l,r,i);
            return;
        }
        int m=(l+r)/2;
        updatecnt(l,m,i*2,x,y,v);
        updatecnt(m+1,r,i*2+1,x,y,v);
        sum[i]=sum[i*2]+sum[i*2+1];
        if(sum[i]==0){
            lzcnt[i]=0;
            pushlzcnt(l,r,i);
        }
        cnt[i]=cnt[i*2]+cnt[i*2+1];
        cerr << "CNT2 : " << l << " " << r << " = " << cnt[i] << "\n";
    }
    void updatecnt(int x,int y,ll v){
        updatecnt(1,n,1,x,y,v);
    }
    void updatesum(int l,int r,int i,int x,int y,ll v){
        pushlzsum(l,r,i);
        pushlzcnt(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y){
            lzsum[i]+=v;
            pushlzsum(l,r,i);
            return;
        }
        int m=(l+r)/2;
        updatesum(l,m,i*2,x,y,v);
        updatesum(m+1,r,i*2+1,x,y,v);
        sum[i]=sum[i*2]+sum[i*2+1];
        if(sum[i]==0){
            lzcnt[i]=0;
            pushlzcnt(l,r,i);
        }
        cnt[i]=cnt[i*2]+cnt[i*2+1];
        cerr << "CNT3 : " << l << " " << r << " = " << cnt[i] << "\n";
    }
    void updatesum(int x,int y,ll v){
        updatesum(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        pushlzsum(l,r,i);
        pushlzcnt(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return cnt[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

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

void hld(int u,int p){
    pos[u]=++posid;
    chain[u]=chainid;
    if(heavy[u])hld(heavy[u],u);
    for(auto v:adj[u]){
        if(v==p||v==heavy[u])continue;
        head[++chainid]=v;
        hld(v,u);
    }
}

void updateupcnt(int st,int ed,ll val){
    while(chain[st]!=chain[ed]){
        seg.updatecnt(pos[head[chain[st]]],pos[st],val);
        st=pa[head[chain[st]]][0];
    }
    seg.updatecnt(pos[ed]+1,pos[st],val);
}

void updateupsum(int st,int ed,ll val){
    while(chain[st]!=chain[ed]){
        seg.updatesum(pos[head[chain[st]]],pos[st],val);
        st=pa[head[chain[st]]][0];
    }
    seg.updatesum(pos[ed]+1,pos[st],val);
}

ll queryup(int st,int ed){
    ll res=0;
    while(chain[st]!=chain[ed]){
        res+=seg.query(pos[head[chain[st]]],pos[st]);
        st=pa[head[chain[st]]][0];
    }
    res+=seg.query(pos[ed]+1,pos[st]);
    return res;
}

int lca(int a,int b){
    if(lv[a]<lv[b])swap(a,b);
    for(int i=19;i>=0;i--)if(lv[pa[a][i]]>=lv[b])a=pa[a][i];
    if(a==b)return a;
    for(int i=19;i>=0;i--)if(pa[a][i]!=pa[b][i])a=pa[a][i],b=pa[b][i];
    return pa[a][0];
}

void add(int u,int v){
    int LCA=lca(u,v);
    updateupsum(u,LCA,1);
    updateupsum(v,LCA,1);
    updateupcnt(u,LCA,1);
    updateupcnt(v,LCA,1);
}

void del(int u,int v){
    int LCA=lca(u,v);
    updateupsum(u,LCA,-1);
    updateupsum(v,LCA,-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    sq=sqrt(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1,0);
    head[++chainid]=1;
    hld(1,0);
    for(int i=1;i<=m;i++)cin >> c[i];
    for(int i=1;i<=q;i++){
        auto &[l,r]=qr[i];
        cin >> l >> r;
        vec[l/sq].emplace_back(i);
    }
    int st=1,ed=1;
    seg.build();
    for(int i=0;i<=sq;i++){
        sort(vec[i].begin(),vec[i].end(),[&](int x,int y){
            return qr[x].second<qr[y].second;
        });
        for(auto j:vec[i]){
            auto [l,r]=qr[j];
            while(st>l){
                add(c[st-1],c[st]);
                st--;
                cerr << st << " " << ed << " : " << seg.query(1,n) << "\n";
                cerr << seg.query(6,6) << ' ' << seg.sum[13] << '\n';
            }
            while(ed<r){
                add(c[ed],c[ed+1]);
                ed++;
                cerr << st << " " << ed << " : " << seg.query(1,n) << "\n";
                cerr << seg.query(6,6) << ' ' << seg.sum[13] << '\n';
            }
            while(st<l){
                del(c[st],c[st+1]);
                st++;
                cerr << st << " " << ed << " : " << seg.query(1,n) << "\n";
                cerr << seg.query(6,6) << ' ' << seg.sum[13] << '\n';
            }
            while(ed>r){
                del(c[ed-1],c[ed]);
                ed--;
                cerr << st << " " << ed << " : " << seg.query(1,n) << "\n";
                cerr << seg.query(6,6) << ' ' << seg.sum[13] << '\n';
            }
            ans[j]=seg.query(1,n)+1;
        }
    }
    for(int i=1;i<=q;i++)cout << ans[i] << '\n';
}