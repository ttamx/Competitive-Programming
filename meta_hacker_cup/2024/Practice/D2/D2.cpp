#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

struct Treap{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val,lz;
        int sz,prio;
        Ptr l,r;
        Node(int _val):val(_val),lz(0),sz(1),prio(rng()),l(),r(){}
    };
    Ptr root;
    Treap():root(){}
    int get_sz(Ptr t){
        return t?t->sz:0;
    }
    void push(Ptr t){
        if(!t)return;
        t->val+=t->lz;
        if(t->l)t->l->lz+=t->lz;
        if(t->r)t->r->lz+=t->lz;
        t->lz=0;
    }
    void pull(Ptr t){
        if(!t)return;
        t->sz=get_sz(t->l)+get_sz(t->r)+1;
    }
    void merge(Ptr &t,Ptr l,Ptr r){
        push(l),push(r);
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        pull(t);
    }
    void split(Ptr t,Ptr &l,Ptr &r,int key){
        push(t);
        if(!t)return void(l=r=nullptr);
        if(t->val<key)split(t->r,t->r,r,key),l=t;
        else split(t->l,l,t->l,key),r=t;
        pull(t);
    }
    void insert(int x){
        Ptr l,r;
        split(root,l,r,x);
        auto t=new Node(x);
        merge(l,l,t);
        merge(root,l,r);
    }
    int query(int k){
        Ptr l,r;
        split(root,l,r,k);
        int res=get_sz(l);
        merge(root,l,r);
        return res;
    }
    void update(int k){
        Ptr l,r;
        split(root,l,r,k);
        if(l)l->lz--;
        merge(root,l,r);
    }
    vector<int> get_all(){
        vector<int> res;
        function<void(Ptr)> rec=[&](Ptr t){
            if(!t)return;
            push(t);
            rec(t->l);
            res.emplace_back(t->val);
            rec(t->r);
        };
        rec(root);
        return res;
    }
    void clear(Ptr t){
        if(!t)return;
        clear(t->l);
        clear(t->r);
        delete t;
    }
    void clear(){
        clear(root);
        root=nullptr;
    }
}tr;

void runcase(){
    int n,g;
    cin >> n >> g;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        int l=0,r=1'500'000;
        while(l<r){
            int m=(l+r+1)/2;
            if(tr.query(m)+a[i]>=m)l=m;
            else r=m-1;
        }
        tr.update(l);
        tr.insert(l);
    }
    pair<int,int> ans(1e9,-1);
    auto b=tr.get_all();
    tr.clear();
    for(int i=0;i<n;i++){
        ans=min(ans,make_pair(abs(g-b[n-i-1]),i));
    }
    cout << ans.second+1 << " " << ans.first << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}