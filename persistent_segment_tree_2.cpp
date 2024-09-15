#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int a[N];
pair<int,int> b[N];

struct PersistentSegmentTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int cnt;
        long long sum;
        Ptr l,r;
        Node():cnt(0),sum(0),l(nullptr),r(nullptr){}
    };
    Ptr root[N];
    void build(int l,int r,Ptr &t){
        t=new Node();
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
            t->cnt++;
            t->sum+=v;
            return;
        }
        int m=(l+r)/2;
        if(x<=m){
            update(l,m,t->l,o->l,x,v);
        }else{
            update(m+1,r,t->r,o->r,x,v);
        }
        t->cnt=t->l->cnt+t->r->cnt;
        t->sum=t->l->sum+t->r->sum;
    }
    void update(int cur,int pre,int x,int v){
        update(1,n,root[cur],root[pre],x,v);
    }
    long long bsearch(int l,int r,Ptr tl,Ptr tr,int k){
        if(l==r)return tr->sum-tl->sum;
        int m=(l+r)/2;
        int cnt=tr->l->cnt-tl->l->cnt;
        long long sum=tr->l->sum-tl->l->sum;
        if(cnt>=k){
            return bsearch(l,m,tl->l,tr->l,k);
        }else{
            return bsearch(m+1,r,tl->r,tr->r,k-cnt)+sum;
        }
    }
    long long bsearch(int vl,int vr,int k){
        return bsearch(1,n,root[vl-1],root[vr],k);
    }
}pst;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        b[i]={a[i],i};
    }
    sort(b+1,b+n+1);
    for(int i=1;i<=n;i++){
        a[b[i].second]=i;
    }
    pst.build(0);
    for(int i=1;i<=n;i++){
        pst.update(i,i-1,a[i],+1);
    }
    while(q--){
        int l,r,k;
        cin >> l >> r >> k;
        cout << b[pst.bsearch(l,r,k)].first << "\n";
    }
}