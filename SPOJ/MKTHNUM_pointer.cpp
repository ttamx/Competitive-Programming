#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int mp[N];
pair<int,int> a[N];

struct node{
    int freq;
    node *l,*r;
    node():freq(0),l(nullptr),r(nullptr){}
    node(int freq):freq(freq),l(nullptr),r(nullptr){}
    node(int freq,node *l,node *r):freq(freq),l(l),r(r){}
};
typedef node* nodeptr;

nodeptr rt[N];

void build(int l,int r,nodeptr &t){
    t=new node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,nodeptr &t,nodeptr k,int x,int val){
    t=new node(*k);
    t->freq+=val;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,k->l,x,val);
    else update(m+1,r,t->r,k->r,x,val);
}

int query(int l,int r,nodeptr tl,nodeptr tr,int val){
    if(l==r)return l;
    int m=(l+r)/2;
    int freq=tr->l->freq-tl->l->freq;
    if(freq<val)return query(m+1,r,tl->r,tr->r,val-freq);
    else return query(l,m,tl->l,tr->l,val);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        cin >> a[i].first;
        a[i].second=i;
    }
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)mp[a[i].second]=i;
    build(1,n,rt[0]);
    for(int i=1;i<=n;i++)update(1,n,rt[i],rt[i-1],mp[i],1);
    while(q--){
        int l,r,k;
        cin >> l >> r >> k;
        cout << a[query(1,n,rt[l-1],rt[r],k)].first << '\n';
    }
}