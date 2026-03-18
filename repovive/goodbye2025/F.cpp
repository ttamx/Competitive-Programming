#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

struct Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val;
        Ptr l,r;
        Node(ll x):val(x),l(),r(){}
    };
    void build(int l,int r,Ptr &t){
        t=new Node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void update(int l,int r,Ptr &t,Ptr o,int x,ll v){
        t=new Node(*o);
        t->val+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,o->l,x,v);
        else update(m+1,r,t->r,o->r,x,v);
    }
    ll query(int l,int r,Ptr tl,Ptr tr,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return tr->val-tl->val;
        int m=(l+r)/2;
        return query(l,m,tl->l,tr->l,x,y)+query(m+1,r,tl->r,tr->r,x,y);
    }
}seg;

struct PrefixMax{
    map<int,int> dat;
    void update(int i,int v){
        i=-i;
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&it->second>=v)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&(--it)->second<=v)it=dat.erase(it);
    }
    int query(int i){
        i=-i;
        auto it=dat.lower_bound(i);
        return it==dat.end()?-1:it->second;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<Segtree::Ptr> root(n+1);
    seg.build(0,n-1,root[0]);
    auto b=a;
    sort(b.begin(),b.end());
    for(int i=0;i<n;i++){
        int idx=lower_bound(b.begin(),b.end(),a[i])-b.begin();
        seg.update(0,n-1,root[i+1],root[i],idx,a[i]);
    }
    mint ans=0;
    PrefixMax ds;
    for(int i=0;i<n;i++){
        ll sum=0;
        ds.update(a[i],i);
        for(int p=i;p>=0;p--){
            int q=ds.query(sum+1);
            if(q==-1||q>p)break;
            while(true){
                int idx=upper_bound(b.begin(),b.end(),sum+1)-b.begin()-1;
                ll new_sum=seg.query(0,n-1,root[q],root[i+1],0,idx);
                if(new_sum<=sum)break;
                sum=new_sum;
            }
            ans+=mint(p-q+1)*mint(sum+1);
            cerr << q << " - " << p << " : " << sum << "\n";
            p=q;
        }
    }
    cerr << "\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}