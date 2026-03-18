#include "boardgames.h"
#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

const int INF=INT_MAX/2;

int n,m;
int l[N],r[N];
vector<int> adj[N];
vector<int> upd[N];
pair<int,int> dp[N];
int fa[N];

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

struct Info{
    int val1,val2,idx;
    Info():val1(INF),val2(0),idx(0){}
    Info(int v1,int v2,int i):val1(v1),val2(v2),idx(i){}
    bool operator<(const Info &o)const{
        if(val1!=o.val1)return val1<o.val1;
        if(val2!=o.val2)return val2<o.val2;
        return idx<o.idx;
    }
};

struct Segtree{
    Info t[K];
    int lz[K];
    void apply(int i,int v){
        t[i].val1+=v;
        lz[i]+=v;
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void modify(int l,int r,int i,int x,Info v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        push(i);
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void modify(int x,Info v){
        modify(0,n,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,int v){
        update(0,n,1,x,y,v);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    Info query(int x,int y){
        return query(0,n,1,x,y);
    }
}seg;


vector<int> partition_players(int _n, int _m,vector<int> _u,vector<int> _v){
    n=_n,m=_m;
    iota(fa+1,fa+n+1,1);
    for(int i=1;i<=n;i++)r[i]=n+1;
    for(int i=0;i<m;i++){
        int u=_u[i]+1,v=_v[i]+1;
        l[v]=max(l[v],u);
        r[u]=min(r[u],v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        upd[r[i]].emplace_back(i);
    }
    dp[0]={0,0};
    seg.modify(0,Info(0,0,0));
    for(int i=1;i<=n;i++){
        dp[i]={dp[i-1].first+1,i-1};
        for(auto j:upd[i]){
            seg.update(l[j],j-1,-1);
        }
        for(auto j:adj[i]){
            fa[fp(i)]=fp(j);
        }
        int id=0;
        for(int j=i-1;j>=1;j--){
            if(fp(i)!=fp(j)){
                id=j;
                break;
            }
        }
        auto res=seg.query(id,l[i]-1);
        if(res.val1==0){
            dp[i]=min(dp[i],make_pair(res.val2+1,res.idx));
        }
        seg.modify(i,Info(0,dp[i].first,i));
        seg.update(l[i],i-1,+1);
    }
    vector<int> ans;
    for(int i=n;i>0;){
        int j=dp[i].second;
        ans.emplace_back(i-j);
        i=j;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}