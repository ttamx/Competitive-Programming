#pragma GCC optimize("O3")
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,m;
ll a[N];

struct node{
    ll val,lz;
    node *l,*r;
    node():val(0),lz(0),l(nullptr),r(nullptr){}
    node(ll val):val(val),lz(0),l(nullptr),r(nullptr){}
    node(ll val,ll lz):val(val),lz(lz),l(nullptr),r(nullptr){}
    node(ll val,ll lz,node* l,node* r):val(val),lz(lz),l(l),r(r){}
};
typedef node* nodeptr;

void build(int l,int r,nodeptr &t){
    t=new node(a[l]);
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
    t->val=t->l->val+t->r->val;
}

void pushlz(int l,int r,nodeptr t){
    if(t->lz==0)return;
    t->val+=t->lz*(r-l+1);
    if(l<r){
        t->l=new node(*(t->l));
        t->r=new node(*(t->r));
        t->l->lz+=t->lz;
        t->r->lz+=t->lz;
    }
    t->lz=0;
}

void update(int l,int r,nodeptr &t,nodeptr k,int x,int y,ll v){
    pushlz(l,r,k);
    if(y<l||r<x)return void(t=k);
    t=new node(*k);
    if(x<=l&&r<=y){
        t->lz+=v;
        pushlz(l,r,t);
        return;
    }
    int m=(l+r)/2;
    update(l,m,t->l,k->l,x,y,v);
    update(m+1,r,t->r,k->r,x,y,v);
    t->val=t->l->val+t->r->val;
}

ll query(int l,int r,nodeptr t,int x,int y){
    pushlz(l,r,t);
    if(y<l||r<x)return 0;
    if(x<=l&&r<=y)return t->val;
    int m=(l+r)/2;
    return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
}

nodeptr rt[N];
int cur=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i];
    build(1,n,rt[0]);
    while(m--){
        char o;
        cin >> o;
        if(o=='C'){
            int l,r,d;
            cin >> l >> r >> d;
            update(1,n,rt[cur+1],rt[cur],l,r,d);
            cur++;
        }else if(o=='Q'){
            int l,r;
            cin >> l >> r;
            cout << query(1,n,rt[cur],l,r) << '\n';
        }else if(o=='H'){
            int l,r,t;
            cin >> l >> r >> t;
            cout << query(1,n,rt[t],l,r) << '\n';
        }else if(o=='B'){
            int t;
            cin >> t;
            cur=t;
        }
    }
}