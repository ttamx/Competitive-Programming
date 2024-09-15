#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int a[N],b[N];

struct PersistentSegmentTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node(int _val):val(_val),l(nullptr),r(nullptr){}
    };
    Ptr root[N];
    void build(int l,int r,Ptr &t){
        t=new Node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int cur){
        build(1,n,root[cur]);
    }
    void update(int l,int r,Ptr &t,Ptr o,int x,int v){
        t=new Node(*o);
        if(l==r){
            t->val++;
            return;
        }
        int m=(l+r)/2;
        if(x<=m){
            update(l,m,t->l,o->l,x,v);
        }else{
            update(m+1,r,t->r,o->r,x,v);
        }
        t->val=t->l->val+t->r->val;
    }
    void update(int cur,int pre,int x,int v){
        update(1,n,root[cur],root[pre],x,v);
    }
    int bsearch(int l,int r,Ptr tl,Ptr tr,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        int cnt=tr->l->val-tl->l->val;
        if(cnt>=k){
            return bsearch(l,m,tl->l,tr->l,k);
        }else{
            return bsearch(m+1,r,tl->r,tr->r,k-cnt);
        }
    }
    int bsearch(int vl,int vr,int k){
        return bsearch(1,n,root[vl-1],root[vr],k);
    }
}pst;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[i]=a[i];
    }
    sort(b+1,b+n+1);
    // compress index
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(b+1,b+n+1,a[i])-b;
    }
    pst.build(0);
    for(int i=1;i<=n;i++){
        pst.update(i,i-1,a[i],+1);
    }
    while(q--){
        int l,r,k;
        cin >> l >> r >> k;
        cout << b[pst.bsearch(l,r,k)] << "\n";
    }
}