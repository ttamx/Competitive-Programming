#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct node {
    ll ans,cnt[5],lz;
    int st,sz,prior,idx;
    bool flip;
    node *l, *r;
    node(int x, int idx) : idx(idx), l(NULL), r(NULL), sz(1), st(x), prior(rand()), lz(-1), flip(false) {cnt[x]=1;}
};
typedef node* pnode;
int get_sz(pnode t) {
    if (!t) return 0;
    else return t->sz;
}
void push(pnode t) {
    if (!t) return;
    if (t->lz!=-1) {
        t->st=t->lz;
        if (t->l) t->l->lz=t->lz;
        if (t->r) t->r->lz=t->lz;
        t->lz=-1;
        t->ans=0;
        for (int i=0; i<5; ++i) t->cnt[i]=0;
        t->cnt[t->st]=t->sz;
    }
}
ll cal(ll x) {return x*(x-1)/2;}
void flip(pnode t) {
    if (!t) return;
    push(t);
    if (t->flip) {
        swap(t->l,t->r);
        t->flip=false;
        if (t->l) t->l->flip^=true;
        if (t->r) t->r->flip^=true;
        t->ans=cal(t->sz)-t->ans;
        for (int i=0; i<5; ++i) t->ans-=cal(t->cnt[i]);
    }
}
void upd(pnode t) {
    if (!t) return;
    push(t);
    flip(t);
    t->sz=1;
    t->ans=0;
    for (int i=0; i<5; ++i) t->cnt[i]=0;
    t->cnt[t->st]=1;
    if (t->l) {
        push(t->l);
        flip(t->l);
        t->sz+=t->l->sz;
        ll sum=t->l->cnt[4];
        for (int i=3; i>=0; --i) {
            t->ans+=t->cnt[i]*sum;
            sum+=t->l->cnt[i];
        }
        for (int i=0; i<5; ++i) t->cnt[i]+=t->l->cnt[i];
        t->ans+=t->l->ans;
    }
    if (t->r) {
        push(t->r);
        flip(t->r);
        t->sz+=t->r->sz;
        ll sum=t->cnt[4];
        for (int i=3; i>=0; --i) {
            t->ans+=t->r->cnt[i]*sum;
            sum+=t->cnt[i];
        }
        for (int i=0; i<5; ++i) t->cnt[i]+=t->r->cnt[i];
        t->ans+=t->r->ans;
    }
}
void split(pnode t, pnode &l, pnode &r, int k) {
    flip(t); push(t);
    if (!t) l=r=NULL;
    else if (get_sz(t->l)<k) split(t->r,t->r,r,k-get_sz(t->l)-1), l=t;
    else split(t->l,l,t->l,k), r=t;
    upd(t);
}
void merge(pnode l, pnode r, pnode &t) {
    flip(l); flip(r); push(l); push(r);
    if (!l) t=r;
    else if (!r) t=l;
    else if (l->prior>r->prior) merge(l->r,r,l->r), t=l;
    else merge(l,r->l,r->l), t=r;
    upd(t);
}
int n,q;
string s;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>q>>s;
    pnode treap=0;
    for (int i=0; i<n; ++i) merge(treap,new node(s[i]-'0',i+1),treap);
    while (q--) {
        int mode; cin>>mode;
        if (mode==1) {
            int a,b,c; cin>>a>>b>>c;
            pnode A,B,C;
            split(treap,A,B,a-1);
            split(B,B,C,b-a+1);
            B->lz=c;
            merge(A,B,treap);
            merge(treap,C,treap);
        } else if (mode==2) {
            int a,b; cin>>a>>b;
            pnode A,B,C;
            split(treap,A,B,a-1);
            split(B,B,C,b-a+1);
            B->flip^=true;
            flip(B);
            merge(A,B,treap);
            merge(treap,C,treap);
        } else {
            int a,b; cin>>a>>b;
            pnode A,B,C;
            split(treap,A,B,a-1);
            split(B,B,C,b-a+1);
            cout<<B->ans<<"\n";
            merge(A,B,treap);
            merge(treap,C,treap);
        }
    }
}
