#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

namespace Treap{
    struct Node{
        int val,prio,sz;
        Node *l,*r;
        Node(int x):val(x),prio(rng()),sz(1),l(nullptr),r(nullptr){}
    };
    using Ptr = Node*;
    int sz(Ptr t){
        return t?t->sz:0;
    }
    void upd(Ptr t){
        if(!t)return;
        t->sz=sz(t->l)+1+sz(t->r);
    }
    void merge(Ptr &t,Ptr l,Ptr r){
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        upd(t);
    }
    void split(Ptr t,Ptr &l,Ptr &r,int key){
        if(!t)return void(l=r=nullptr);
        if(sz(t->l)+1<=key)split(t->r,t->r,r,key-sz(t->l)-1),l=t;
        else split(t->l,l,t->l,key),r=t;
        upd(t);
    }
    Ptr first(Ptr t){
        while(t->l)t=t->l;
        return t;
    }
    Ptr last(Ptr t){
        while(t->r)t=t->r;
        return t;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n),adj2(n),adj3(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    Treap::Ptr root=nullptr;
    vector<int> pre(n,-1),nxt(n,-1);
    vector<int> ord(n);
    function<void(int)> dfs=[&](int u){
        int val=a[u];
        Treap::Ptr t1,t2,t3;
        Treap::split(root,t1,t2,val);
        if(t1){
            pre[u]=Treap::last(t1)->val;
        }
        if(t2){
            nxt[u]=Treap::first(t2)->val;
        }
        Treap::merge(root,t1,new Treap::Node(u));
        Treap::merge(root,root,t2);
        for(auto v:adj[u]){
            dfs(v);
        }
        Treap::split(root,t1,t2,val);
        Treap::split(t2,t2,t3,1);
        Treap::merge(root,t1,t3);
        ord.emplace_back(u);
    };
    dfs(0);
    mint ans=1;
    map<pair<int,int>,int> ss;
    vector<int> sz(n);
    for(auto x:ord){
        int u=pre[x],v=nxt[x];
        if(u!=-1&&v!=-1){
            int s1=ss[{u,x}];
            int s2=ss[{x,v}];
            ans*=comb.fac(s1);
            ans*=comb.fac(s2);
            int s=s1+s2+1;
            ss[{u,v}]+=s;
            ans*=comb.ifac(s);
        }else if(u!=-1){
            int s=ss[{u,x}];
            ans*=comb.fac(s);
            sz[x]=s+1;
            adj2[u].emplace_back(x);
        }else if(v!=-1){
            int s=ss[{x,v}];
            ans*=comb.fac(s);
            sz[x]=s+1;
            adj3[v].emplace_back(x);
        }else{
            assert(x==0);
        }
    }
    function<int(int)> dfs2=[&](int u){
        int s=0;
        for(auto v:adj2[u]){
            int t=dfs2(v);
            ans*=comb.ifac(t);
            s+=t;
        }
        ans*=comb.fac(s);
        return s+sz[u];
    };
    dfs2(0);
    function<int(int)> dfs3=[&](int u){
        int s=0;
        for(auto v:adj3[u]){
            int t=dfs3(v);
            ans*=comb.ifac(t);
            s+=t;
        }
        ans*=comb.fac(s);
        return s+sz[u];
    };
    dfs3(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}