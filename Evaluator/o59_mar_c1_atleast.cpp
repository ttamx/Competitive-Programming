#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef double db;

const int N=1e5+5;

struct node{
    db v;
    int f;
    node *l,*r;
    node():v(0),f(0),l(nullptr),r(nullptr){}
    node(db v,int f):v(v),f(f),l(nullptr),r(nullptr){}
    node(db v,int f,node *l,node *r):v(v),f(f),l(l),r(r){}
};

typedef node* nodeptr;

int n,m;
db u;
db a[N],qs[N];
nodeptr rt[N];
int mp[N];
vector<pair<db,int>> tb;

void build(int l,int r,nodeptr &t){
    t=new node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
    t->v=t->l->v+t->r->v;
    t->f=t->l->f+t->r->f;
}

void update(int l,int r,nodeptr &t,int x,db v,nodeptr k){
    t=new node(*k);
    t->v+=v;
    t->f++;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,x,v,k->l);
    else update(m+1,r,t->r,x,v,k->r);
}

db query(int l,int r,nodeptr t,nodeptr k,int v){
    if(v<=0)return 0;
    if(l==r)return k->v-t->v;
    db sum=k->r->v-t->r->v;
    int freq=k->r->f-t->r->f;
    int m=(l+r)/2;
    if(freq<=v)return sum+query(l,m,t->l,k->l,v-freq);
    return query(m+1,r,t->r,k->r,v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        qs[i]=a[i]+qs[i-1];
        tb.emplace_back(a[i],i);
    }
    sort(tb.begin(),tb.end());
    for(int i=0;i<n;i++)mp[tb[i].second]=i+1;
    build(1,n,rt[0]);
    for(int i=1;i<=n;i++)update(1,n,rt[i],mp[i],a[i],rt[i-1]);
    while(m--){
        int st,ed;
        cin >> st >> ed >> u;
        int sz=ed-st+1;
        int l=0,r=sz;
        while(l<r){
            int mid=(l+r+1)/2;
            if(query(1,n,rt[st-1],rt[ed],mid)>=u*mid)l=mid;
            else r=mid-1;
        }
        cout << (l>0?sz-l:-1) << '\n';
    }
}