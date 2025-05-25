#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=300005;
const int K=1<<20;
const int L=1e9;

int n,k;
int l[N],r[N];

struct Info{
    int val,cnt;
    Info():val(0),cnt(0){}
    Info(int v,int c):val(v),cnt(c){}
    friend Info operator+(const Info &l,const Info &r){
        if(l.val<r.val)return l;
        if(r.val<l.val)return r;
        return Info{l.val,l.cnt+r.cnt};
    }
};

struct Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        Info val;
        int lz;
        Ptr l,r;
        Node():val(),lz(0),l(),r(){}
        Node(int s):val(0,s),lz(0),l(),r(){}
    };
    Ptr root=new Node(L);
    void apply(int l,int r,Ptr &t,int v){
        if(!t)t=new Node(r-k+1);
        t->val.val+=v;
        t->lz+=v;
    }
    void push(int l,int m,int r,Ptr t){
        apply(l,m,t->l,t->lz);
        apply(m+1,r,t->r,t->lz);
        t->lz=0;
    }
    void update(int l,int r,Ptr t,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,t,v);
        int m=(l+r)/2;
        push(l,m,r,t);
        update(l,m,t->l,x,y,v);
        update(m+1,r,t->r,x,y,v);
        t->val=t->l->val+t->r->val;
    }
    void update(int x,int y,int v){update(1,L,root,x,y,v);}
    void clear(Ptr t){
        if(!t)return;
        t->val.val=0;
        t->lz=0;
        clear(t->l);
        clear(t->r);
    }
    void clear(){clear(root);}
    int query(){
        if(root->val.cnt>0)return L;
        return L-root->val.cnt;
    }
}seg;

pair<ll,ll> solve(ll mid){
    pair<ll,ll> res;
    for(int i=1,j=1;i<=n;i++){
        for(;j<=n&&seg.query()<mid;j++)seg.update(l[j],r[j],+1);
        if(seg.query()<mid)break;
        ans+=seg.query();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;

}