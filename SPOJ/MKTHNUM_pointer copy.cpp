#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int mp[N];
pair<int,int> a[N];

struct persist{
    struct node;
    typedef node* pnode;
    struct node{
        int cnt;
        pnode l,r;
        node(int x):cnt(x),l(nullptr),r(nullptr){}
    };
    pnode rt[N];
    void build(int l,int r,pnode &t){
        t=new node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int cur){
        build(1,n,rt[cur]);
    }
    void update(int l,int r,pnode &t,int x,int v,pnode k){
        t=new node(*k);
        t->cnt+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v,k->l);
        else update(m+1,r,t->r,x,v,k->r);
    }
    void update(int pre,int cur,int x,int v){
        update(1,n,rt[cur],x,v,rt[pre]);
    }
    int query(int l,int r,pnode tl,pnode tr,int k){
        if(l==r)return l;
        int cnt=tr->l->cnt-tl->l->cnt;
        int m=(l+r)/2;
        if(cnt>=k)return query(l,m,tl->l,tr->l,k);
        else return query(m+1,r,tl->r,tr->r,k-cnt);
    }
    int query(int l,int r,int k){
        return query(1,n,rt[l],rt[r],k);
    }
}pst;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)mp[a[i].second]=i;
    pst.build(0);
    for(int i=1;i<=n;i++)pst.update(i-1,i,mp[i],1);
    while(q--){
        int l,r,k;
        cin >> l >> r >> k;
        cout << a[pst.query(l-1,r,k)].first << '\n';
    }
}