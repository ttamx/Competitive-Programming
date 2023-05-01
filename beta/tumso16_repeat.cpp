#include<bits/stdc++.h>

using namespace std;

const int N=5e4+5;

int n,q;
map<int,int> mp;

struct persist{
    struct node{
        int val;
        node *l,*r;
        node(int val):val(val),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt[N];
    void build(int l,int r,pnode &t){
        t=new node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int ver){
        build(1,n,rt[ver]);
    }
    void update(int l,int r,pnode &t,pnode &k,int &x,int &v){
        t=new node(*k);
        t->val+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,v);
        else update(m+1,r,t->r,k->r,x,v);
    }
    void update(int pre,int cur,int x,int v){
        update(1,n,rt[cur],rt[pre],x,v);
    }
    int query(int l,int r,pnode &t,int &x,int &y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    int query(int ver,int x,int y){
        return query(1,n,rt[ver],x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    s.build(0);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        s.update(i-1,i,i,1);
        if(mp[x])s.update(i,i,mp[x],-1);
        mp[x]=i;
    }
    int k=1;
    while(q--){
        int x;
        cin >> x;
        if(x>k)swap(x,k);
        int now=s.query(k,x,k);
        k=(now%n)+1;
        cout << now << '\n';
    }
}