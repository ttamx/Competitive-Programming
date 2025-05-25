#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct LCT{
    struct Node;
    using Ptr = Node*;
    struct Node{
        Ptr ch[2],p;
        ll val,sum;
        bool rev;
        Node(ll v):ch{nullptr,nullptr},p(nullptr),val(v),sum(v),rev(false){}
    };
    void toggle(Ptr v){
        if(!v)return;
        swap(v->ch[0],v->ch[1]);
        v->rev^=true;
    }
    void push(Ptr v){
        if(!v||!(v->rev))return;
        toggle(v->ch[0]),toggle(v->ch[1]);
        v->rev=false;
    }
    void pull(Ptr v){
        if(!v)return;
        v->sum=v->val;
        if(v->ch[0])v->sum+=v->ch[0]->sum;
        if(v->ch[1])v->sum+=v->ch[1]->sum;
    }
    bool is_root(Ptr v){
        return !v->p||(v->p->ch[0]!=v&&v->p->ch[1]!=v);
    }
    bool pos(Ptr v){
        return v->p->ch[1]==v;
    }
    void rotate(Ptr v){
        Ptr u=v->p,g=u->p;
        bool x=pos(v);
        if(!is_root(u))g->ch[pos(u)]=v;
        u->ch[x]=v->ch[!x];
        if(u->ch[x])u->ch[x]->p=u;
        v->ch[!x]=u,u->p=v,v->p=g;
        pull(u),pull(v);
    }
    void splay(Ptr v){
        if(!v)return;
        for(push(v);!is_root(v);rotate(v)){
            Ptr u=v->p;
            if(is_root(u))push(u),push(v);
            else push(u->p),push(u),push(v),rotate(pos(u)==pos(v)?u:v);
        }
    }
    void access(Ptr v){
        for(Ptr u=v,c=nullptr;u;u=u->p){
            splay(u);
            u->ch[1]=c;
            pull(u);
            c=u;
        }
        splay(v);
    }
    void evert(Ptr v){
        access(v);
        toggle(v);
    }
    void link(Ptr u,Ptr v){
        evert(u);
        access(v);
        u->p=v;
    }
    void cut(Ptr u,Ptr v){
        evert(u);
        access(v);
        assert(u->p==v);
        v->ch[0]=u->p=nullptr;
        pull(u);
    }
    ll aggregate(Ptr u,Ptr v){
        evert(u);
        access(v);
        return v->sum;
    }
    void set(Ptr v,ll val){
        evert(v);
        v->val=val;
        pull(v);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    LCT lct;
    vector<ll> a(n);
    vector<LCT::Ptr> ptr(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        ptr[i]=new LCT::Node(a[i]);
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        lct.link(ptr[u],ptr[v]);
    }
    while(q--){
        int t;
        cin >> t;
        if(t==0){
            int u,v,x,y;
            cin >> u >> v >> x >> y;
            lct.cut(ptr[u],ptr[v]);
            lct.link(ptr[x],ptr[y]);
        }else if(t==1){
            int u,x;
            cin >> u >> x;
            a[u]+=x;
            lct.set(ptr[u],a[u]);
        }else{
            int u,v;
            cin >> u >> v;
            cout << lct.aggregate(ptr[u],ptr[v]) << "\n";
        }
    }
}