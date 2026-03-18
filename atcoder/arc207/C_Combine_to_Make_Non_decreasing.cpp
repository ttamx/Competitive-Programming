#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;
const int N=2e5+5;
const int B=30;

struct Node;
using Ptr = Node*;
struct Node{
    int mx;
    Ptr l,r;
    Node():mx(-INF),l(),r(){}
};

int get(Ptr t){
    return t?t->mx:-INF;
}

Ptr merge(Ptr l,Ptr r){
    if(!l)return r;
    if(!r)return l;
    l->l=merge(l->l,r->l);
    l->r=merge(l->r,r->r);
    l->mx=max({get(l),get(r),get(l->l),get(l->r)});
    return l;
}

void insert(int l,int r,Ptr &t,int x,int v){
    if(!t)t=new Node();
    t->mx=max(t->mx,v);
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)insert(l,m,t->l,x,v);
    else insert(m+1,r,t->r,x,v);
}

int query(int l,int r,Ptr t,int x,int y){
    if(y<l||r<x||!t)return -INF;
    if(x<=l&&r<=y)return t->mx;
    int m=(l+r)/2;
    return max(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
}

int n;
int a[N];
int last[B];
int fa[N];
Ptr root[N];
int cnt[N];
int mask[N];

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

void merge(int u,int v){
    u=fp(u),v=fp(v);
    assert(u!=v);
    fa[v]=u;
    root[u]=merge(root[u],root[v]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<=n;i++){
        root[i]=new Node();
    }
    cnt[0]=INF;
    insert(0,(1<<B)-1,root[0],0,0);
    iota(fa,fa+n+1,0);
    int ans=-INF;
    set<int,greater<int>> pos;
    for(int i=1;i<=n;i++){
        int x=a[i];
        for(int j=0;j<B;j++){
            if(a[i]>>j&1){
                if(--cnt[last[j]]==0){
                    pos.erase(last[j]);
                    merge(last[j]-1,last[j]);
                }
                last[j]=i;
                cnt[i]++;
            }
        }
        mask[i]=a[i];
        pos.emplace(i);
        for(auto j:pos){
            x|=mask[j];
            int dp=query(0,(1<<B)-1,root[fp(j-1)],0,x)+1;
            if(dp>=0){
                insert(0,(1<<B)-1,root[i],x,dp);
            }
            if(i==n){
                ans=max(ans,dp);
            }
        }
    }
    cout << ans << "\n";
}