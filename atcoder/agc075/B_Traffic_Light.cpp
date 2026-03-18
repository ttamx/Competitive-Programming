#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val,add,ch;
        Ptr l,r;
        Node():val(0),add(0),ch(0),l(),r(){}
    };
    Ptr root;
    Segtree():root(new Node()){}
    void apply(Ptr &t,ll add,ll ch){
        if(!t)t=new Node();
        t->val=max(t->val+add,ch);
        t->add+=add;
        t->ch=max(t->ch+add,ch);
    }
    void push(Ptr t){
        apply(t->l,t->add,t->ch);
        apply(t->r,t->add,t->ch);
        t->add=t->ch=0;
    }
    void pull(Ptr t){
        t->val=max(t->l->val,t->r->val);
    }
    void update(int l,int r,Ptr &t,int x,int y,ll add,ll ch){
        if(y<l||r<x||l>r)return;
        if(x<=l&&r<=y)return apply(t,add,ch);
        push(t);
        int m=(l+r)/2;
        update(l,m,t->l,x,y,add,ch);
        update(m+1,r,t->r,x,y,add,ch);
        pull(t);
    }
};

void runcase(){
    int n,p,x,y;
    cin >> n >> p >> x >> y;
    vector<ll> a(n),c(n);
    for(auto &e:a)cin >> e,e+=y;
    for(auto &e:c)cin >> e;
    vector<tuple<ll,int,int>> event;
    for(int i=0;i<n;i++){
        event.emplace_back(a[i]-x+1,i,1);
        event.emplace_back(a[i]+1,i,2);
    }
    sort(event.begin(),event.end());
    Segtree seg;
    ll l=0,r=0,d=-p;
    for(int i=0;i<event.size();i++){
        auto [t,j,op]=event[i];
        r=t;
        if(l<r){
            ll t=(r-l)/y;
            ll v=max(d,0LL);
            if(t>0){
                seg.update(0,y-1,seg.root,0,y-1,t*v,seg.root->val);
            }
            l+=t*y;
            if(l%y<=r%y){
                seg.update(0,y-1,seg.root,l%y,r%y-1,v,seg.root->val);
            }else{
                seg.update(0,y-1,seg.root,l%y,y-1,v,seg.root->val);
                seg.update(0,y-1,seg.root,0,r%y-1,v,seg.root->val);
            }
            l=r;
        }
        if(op==1)d+=c[j];
        else d-=c[j];
    }
    cout << seg.root->val << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}