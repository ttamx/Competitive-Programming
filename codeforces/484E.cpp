#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

struct info{
    int sum,mx,pre,suf;
    info():sum(0),mx(0),pre(0),suf(0){}
    info(int sum):sum(sum),mx(0),pre(0),suf(0){}
    info(int sum,int x):sum(sum),mx(x),pre(x),suf(x){}
    info(int sum,int mx,int pre,int suf):sum(sum),mx(mx),pre(pre),suf(suf){}
    friend info operator+(info a,info b){
        info c;
        c.sum=a.sum+b.sum;
        if(a.mx!=a.sum)c.pre=a.pre;
        else c.pre=a.mx+b.pre;
        if(b.mx!=b.sum)c.suf=b.suf;
        else c.suf=b.mx+a.suf;
        c.mx=max({a.suf+b.pre,a.mx,b.mx});
        return c;
    }
};

struct node{
    info val;
    node *l,*r;
    node():val(),l(nullptr),r(nullptr){}
    node(int sum,int x):val(info(sum,x)),l(nullptr),r(nullptr){}
    node(int sum,int x,node *l,node *r):val(info(sum,x)),l(l),r(r){}
    void upd(){
        val=l->val+r->val;
    }
};
typedef node* nodeptr;

void build(int l,int r,nodeptr &t){
    if(l==r)return void(t=new node(1,0));
    t=new node();
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
    t->upd();
}

void update(int l,int r,nodeptr &t,nodeptr k,int x,int v){
    if(l==r)return void(t=new node(1,v));
    t=new node(*k);
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,k->l,x,v);
    else update(m+1,r,t->r,k->r,x,v);
    t->upd();
}

info query(int l,int r,nodeptr t,int x,int y){
    if(y<l||r<x)return info();
    if(x<=l&&r<=y)return t->val;
    int m=(l+r)/2;
    return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
}

int n,q;
nodeptr rt[N];
int a[N];
map<int,vector<int>> vec;
int val[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        vec[a[i]].emplace_back(i);
    }
    int idx=0;
    for(auto [h,v]:vec)val[++idx]=h;
    build(1,n,rt[idx+1]);
    for(int i=idx;i>0;i--){
        auto res=vec[val[i]];
        rt[i]=rt[i+1];
        for(auto j:res)update(1,n,rt[i],rt[i],j,1);
    }
    cin >> q;
    while(q--){
        int x,y,w; 
        cin >> x >> y >> w;
        int l=0,r=idx;
        while(l<r){
            int m=(l+r+1)/2;
            int res=query(1,n,rt[m],x,y).mx;
            if(res>=w)l=m;
            else r=m-1;
        }
        cout << val[l] << '\n';
    }
}