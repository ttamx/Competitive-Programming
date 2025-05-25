#include<bits/stdc++.h>

using namespace std;

const int N=200005;

int n,m,q;
int eu[N],ev[N],opt[N];

struct DSU{
    int p[N],sz[N],c[N];
    bool ans;
    int t;
    vector<tuple<int,int,int,bool,int>> s;
    void init(){
        for(int i=1;i<=n;i++)p[i]=i,sz[i]=1,c[i]=0;
        ans=true;
        t=0;
        s.clear();
    }
    int fp(int u){return u==p[u]?u:fp(p[u]);}
    int col(int u){return c[u]^(u==p[u]?0:col(p[u]));}
    int uni(int i){
        t++;
        int u=eu[i],v=ev[i];
        int d=col(u)^col(v)^1;
        u=fp(u),v=fp(v);
        if(u==v){
            if(d&&ans){
                s.emplace_back(t,0,0,ans,i);
                ans=false;
            }
        }else{
            if(sz[u]<sz[v])swap(u,v);
            c[v]^=c[u]^d;
            sz[u]+=sz[v];
            p[v]=u;
            s.emplace_back(t,u,v,ans,i);
        }
        return t;
    }
    void rollback(int x){
        t=x;
        while(!s.empty()){
            auto [tt,u,v,a,i]=s.back();
            if(tt<=t)break;
            if(u){
                sz[u]-=sz[v];
                p[v]=v;
            }
            ans=a;
            s.pop_back();
        }
    }
}dsu;

void dnc(int l,int r,int optl,int optr){
    if(l>r)return;
    int m=(l+r)/2;
    opt[m]=optr;
    int t1=dsu.t;
    for(int i=l;i<m;i++)dsu.uni(i);
    int t2=dsu.t;
    while(dsu.ans&&opt[m]>=max(m,optl+1))dsu.uni(opt[m]--);
    dsu.rollback(t2);
    dsu.uni(m);
    dnc(m+1,r,opt[m],optr);
    dsu.rollback(t1);
    for(int i=optr;i>opt[m];i--)dsu.uni(i);
    dnc(l,m-1,optl,opt[m]);
    dsu.rollback(t1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=m;i++)cin >> eu[i] >> ev[i];
    dsu.init();
    dnc(1,m,0,m);
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << (opt[l]>=r?"YES":"NO") << "\n";
    }
}