#include<bits/stdc++.h>
#pragma GCC optimize("Ofast, unroll-loops")

using namespace std;

using ll = long long;

struct LCT{
    struct Node;
    using Ptr = Node*;
    struct Node{
        Ptr ch[2],p;
        int val,sum;
        bool rev;
        Node(int v):ch{nullptr,nullptr},p(nullptr),val(v),sum(v),rev(false){}
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
    int aggregate(Ptr u,Ptr v){
        evert(u);
        access(v);
        return v->sum;
    }
    void set(Ptr v,int val){
        evert(v);
        v->val=val;
        pull(v);
    }
};

using Node = LCT::Node;
using Ptr = LCT::Ptr;

void runcase(){
    int n,d;
    cin >> n >> d;
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a.emplace_back(x,i);
    }
    sort(a.begin(),a.end());
    LCT lct;
    vector<Ptr> ptr(n+1),par(n);
    for(int i=0;i<=n;i++)ptr[i]=new Node(i<n);
    for(int i=0;i<n;i++){
        lct.link(ptr[i],par[i]=ptr[min(i+d,n)]);
    }
    ll ans=0;
    int last=0;
    set<int> s;
    for(int i=0;i<=n;i++)s.emplace(i);
    for(auto [h,i]:a){
        ll diff=h-last;
        ans+=diff*lct.aggregate(ptr[0],ptr[n]);
        auto it=s.find(i);
        it=s.erase(it);
        assert(it!=s.end());
        lct.cut(ptr[i],par[i]);
        lct.link(ptr[i],par[i]=ptr[*it]);
        lct.set(ptr[i],0);
        last=h;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}