#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

const int N=200005;

int n;
int a[N];
int mxl[N],mxr[N];
vector<tuple<int,int,int>> upd[N];

struct Node;
using Ptr = Node*;
struct Node{
    int v;
    Ptr l,r;
    Node():v(0),l(),r(){}
};
Ptr root[N];
void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}
void update(int l,int r,Ptr &t,Ptr o,int x,int v){
    t=new Node(*o);
    t->v+=v;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,o->l,x,v);
    else update(m+1,r,t->r,o->r,x,v);
}
int query(int l,int r,Ptr t,int x,int y){
    if(y<l||r<x||!t)return 0;
    if(x<=l&&r<=y)return t->v;
    int m=(l+r)/2;
    return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
}
void add(int l1,int r1,int l2,int r2){
    upd[l1].emplace_back(l2,r2,+1);
    upd[r1+1].emplace_back(l2,r2,-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int t=0;t<2;t++){
        {
            vector<int> s{0};
            for(int i=1;i<=n;i++){
                while(s.size()>1&&a[s.back()]<a[i])s.pop_back();
                mxl[i]=s.back();
                s.emplace_back(i);
            }
        }
        {
            vector<int> s{n+1};
            for(int i=n;i>=1;i--){
                while(s.size()>1&&a[s.back()]<a[i])s.pop_back();
                mxr[i]=s.back();
                s.emplace_back(i);
            }
        }
        SegmentTree<MinMonoid<int>> seg(n+1,[&](int i){return a[i];});
        for(int i=1;i<=n;i++){
            if(mxr[i]>n)continue;
            int x=seg.findfirst(mxr[i],n,[&](int x){return x<a[i];});
            add(mxl[i]+1,i,mxr[i],x-1);
        }
        for(int i=1;i<=n;i++)a[i]=n-a[i]+1;
    }
    build(1,n,root[0]);
    for(int i=1;i<=n;i++){
        root[i]=root[i-1];
        for(auto [l,r,v]:upd[i]){
            update(1,n,root[i],root[i],l,v);
            if(r<n)update(1,n,root[i],root[i],r+1,-v);
        }
    }
    int q;
    cin >> q;
    for(int qi=1;qi<=q;qi++){
        int l,r;
        cin >> l >> r;
        cout << (query(1,n,root[l],1,r)?"YES":"NO") << "\n";
        if(qi%10==0)cout << flush;
    }
}