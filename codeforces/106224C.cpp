#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
long long ans=0;

struct KRT{
    int fa[N],wt[N],l[N],r[N],tin[N],tout[N],node[N],dep[N],par[N],jump[N],sz[N];
    int timer=0;
    int fp(int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    }
    void init(){
        vector<tuple<int,int,int>> e(n-1);
        for(auto &[w,u,v]:e){
            cin >> u >> v >> w;
        }
        for(int i=1;i<=2*n;i++){
            fa[i]=i;
        }
        int buf=n;
        sort(e.begin(),e.end());
        for(auto [w,u,v]:e){
            u=fp(u),v=fp(v);
            assert(u!=v);
            buf++;
            fa[u]=fa[v]=par[u]=par[v]=buf;
            wt[buf]=w;
            l[buf]=u;
            r[buf]=v;
        }
        for(int u=1;u<=buf;u++){
            sz[u]=1+sz[l[u]]+sz[r[u]];
            if(sz[l[u]]<sz[r[u]])swap(l[u],r[u]);
        }
        dfs(buf);
        par[buf]=jump[buf]=buf;
        for(int u=buf-1;u>=1;u--){
            int p=par[u];
            int x=jump[p];
            int y=jump[x];
            dep[u]=dep[par[u]]+1;
            jump[u]=(dep[p]-dep[x]==dep[x]-dep[y]?y:p);
        }
    }
    void dfs(int u){
        if(!u)return;
        tin[u]=++timer;
        node[timer]=u;
        dfs(l[u]);
        dfs(r[u]);
        tout[u]=timer;
    }
    int lift(int u,int w){
        while(u!=par[u]&&wt[par[u]]<=w){
            if(wt[jump[u]]<=w)u=jump[u];
            else u=par[u];
        }
        return u;
    }
}t1,t2;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int query(int l,int r){
        return query(r)-query(l-1);
    }
}f;

inline void update(int i,int v){
    if(i<=n){
        f.update(t1.tin[i],v);
    }
}

void sack(int u,bool del){
    if(t2.r[u])sack(t2.r[u],true);
    if(t2.l[u])sack(t2.l[u],false);
    update(u,+1);
    if(t2.r[u]){
        for(int i=t2.tin[t2.r[u]];i<=t2.tout[t2.r[u]];i++){
            int v=t2.node[i];
            if(v>n)continue;
            v=t1.lift(v,t2.wt[u]);
            ans+=f.query(t1.tin[v],t1.tout[v]);
        }
    }
    if(del){
        update(u,-1);
        if(t2.l[u]){
            for(int i=t2.tin[t2.l[u]];i<=t2.tout[t2.l[u]];i++){
                update(t2.node[i],-1);
            }
        }
    }else{
        if(t2.r[u]){
            for(int i=t2.tin[t2.r[u]];i<=t2.tout[t2.r[u]];i++){
                update(t2.node[i],+1);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    t1.init();
    t2.init();
    sack(n*2-1,false);
    cout << ans << "\n";
}