#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;

int n,q;
vector<int> factor[N];

struct segtree{
    struct node;
    typedef node* pnode;
    struct node{
        int val;
        pnode l,r;
        node(int val=-1):val(val),l(nullptr),r(nullptr){}
    };
    pnode rt;
    segtree():rt(nullptr){};
    void update(int l,int r,pnode &t,int x,int v){
        if(!t)t=new node();
        t->val=max(t->val,v);
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
    }
    void update(int x,int v){
        update(1,n,rt,x,v);
    }
    int query(int l,int r,pnode &t,int x,int y){
        if(!t||y<l||r<x)return -1;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return max(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    int query(int x,int y){
        return query(1,n,rt,x,y);
    }
}s[N];

int main(){                     
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(!factor[i].empty())continue;
        for(int j=i;j<N;j+=i)factor[j].emplace_back(i);
    }
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        for(auto p:factor[x])s[p].update(i,x);
    }
    while(q--){
        int l,r,x;
        cin >> l >> r >> x;
        int ans=-1;
        for(auto p:factor[x])ans=max(ans,s[p].query(l,r));
        cout << ans << "\n";
    }
}