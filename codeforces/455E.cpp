#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll inf=1e18;

int n,m;
ll a[N];

struct line{
    ll m,c;
    line():m(0),c(inf){}
    line(ll m,ll c):m(m),c(c){}
    ll get(ll x){
        return m*x+c;
    }
};

struct lichao{
    struct node;
    typedef node* pnode;
    struct node{
        line val;
        pnode l,r;
        node():val(),l(nullptr),r(nullptr){}
    };
    pnode rt=nullptr;
    void update(int l,int r,pnode &t,line v){
        if(!t)t=new node();
        int m=(l+r)/2;
        if(v.get(m)<t->val.get(m))swap(v,t->val);
        if(v.get(l)<t->val.get(l))update(l,m,t->l,v);
        if(v.get(r)<t->val.get(r))update(m+1,r,t->r,v);
    }
    void update(line v){
        update(-N,0,rt,v);
    }
    ll query(int l,int r,pnode t,ll x){
        if(x<l||r<x)return inf;
        ll res=t->val.get(x);
        if(l==r)return res;
        return min({res,query(l,m,t->l,x),query(m+1,r,t->r,x)});
    }
    ll query(ll x){
        return query(-N,0,rt,x);
    }
};



int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    cin >> m;
}