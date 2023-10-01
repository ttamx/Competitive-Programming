#include<bits/stdc++.h>

using namespace std;

const int N=4e5+5;
const int inf=1e9;

int n,mx;
int a[N],l[N],r[N],ans[N];

struct segtree{
    struct node{
        int val;
        node *l,*r;
        node():val(0),l(nullptr),r(nullptr){}
    };
    typedef node* pnode;
    pnode rt=nullptr;
    int getval(pnode t){
        return t?t->val:0;
    }
    void update(int l,int r,pnode &t,int x,int v){
        if(!t)t=new node();
        if(l==r)return void(t->val=max(t->val,v));
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
        t->val=max(getval(t->l),getval(t->r));
    }
    void update(int x,int v){
        update(1,inf,rt,x,v);
    }
    int query(int l,int r,pnode t,int x,int y){
        if(y<l||r<x)return 0;
        if(!t)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return max(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    int query(int x,int y){
        return query(1,inf,rt,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    iota(a,a+n+1,0);
    sort(a+1,a+n+1,[&](int i,int j){
        if(r[i]!=r[j])return r[i]<r[j];
        return l[i]>l[j];
    });
    for(int i=1;i<=n;i++){
        ans[a[i]]=s.query(l[a[i]],r[a[i]])+1;
        mx=max(mx,ans[a[i]]);
        s.update(l[a[i]],ans[a[i]]);
    }
    cout << mx << "\n";
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}