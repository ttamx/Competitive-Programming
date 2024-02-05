#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

const int N=4e5+5;
const int K=1<<19;

int n,m,id;
int fa[N];
int pw[N];
pair<int,int> ch[N];
vector<tuple<int,int,int,int,int>> vec;
int tin[N],tout[N];
int timer;

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

struct Info{
    int sz,val;
    Info():sz(0),val(0){}
    Info(int _sz,int _val):sz(_sz),val(_val){}
    Info &operator+=(const Info &rhs){
        val=(1LL*val*pw[rhs.sz]+rhs.val)%MOD;
        sz+=rhs.sz;
        return *this;
    }
    friend Info operator+(const Info &lhs,const Info &rhs){
        return Info(lhs)+=rhs;
    }
};

struct segtree{
    Info t[K],lz[K];
    void push(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=Info();
    }
    void update(int l,int r,int i,int x,int y,const Info &v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,const Info &v){
        update(1,n,1,x,y,v);
    }
    Info query(int l,int r,int i,int x){
        push(l,r,i);
        if(l==r)return t[i];
        int m=(l+r)/2;
        if(x<=m)return query(l,m,i*2,x);
        else return query(m+1,r,i*2+1,x);
    }
    Info query(int x){
        return query(1,n,1,x);
    }
}s;

void dfs(int u){
    tin[u]=timer+1;
    if(u>n){
        dfs(ch[u].first);
        dfs(ch[u].second);
    }else{
        timer++;
    }
    tout[u]=timer;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*10LL%MOD;
    for(int i=1;i<=n;i++)fa[i]=i;
    id=n;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        int fu=fp(u),fv=fp(v);
        if(fu==fv)continue;
        fa[fu]=fa[fv]=++id;
        ch[id]={fu,fv};
        fa[id]=id;
        vec.emplace_back(u,v,fu,fv,i);
    }
    dfs(id);
    for(auto [u,v,fu,fv,i]:vec){
        Info du=s.query(tin[u]);
        Info dv=s.query(tin[v]);
        s.update(tin[fu],tout[fu],Info(1,i)+dv);
        s.update(tin[fv],tout[fv],Info(1,i)+du);
    }
    for(int i=1;i<=n;i++)cout << s.query(tin[i]).val << "\n";
}