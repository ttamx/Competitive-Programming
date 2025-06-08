#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int Q=2e5+5;
const int K=1<<20;
const int KK=1<<19;
const int INF=INT_MAX/2;

int n,m,q;
vector<int> vals;
int st[Q],ed[Q];
int ans[Q];
char op[Q];

struct Sign{
    int l,r,h;
}a[Q];

struct Query{
    int l,r;
}qr[Q];

namespace Segtree{
    int timer;
    struct RollbackArray{
        int a[K];
        stack<tuple<int,int,int>> upd;
        void set(int i,int x){
            upd.emplace(timer,i,a[i]);
            a[i]=x;
        }
        void rollback(int t){
            while(!upd.empty()){
                auto [tt,i,v]=upd.top();
                if(tt<=t)break;
                upd.pop();
                a[i]=v;
            }
        }
    };
    RollbackArray t,lz;
    void apply(int i,int v){
        t.set(i,max(t.a[i],v));
        lz.set(i,max(lz.a[i],v));
    }
    void push(int i){
        apply(i*2,lz.a[i]);
        apply(i*2+1,lz.a[i]);
        lz.set(i,0);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<=l||r<=x)return;
        if(x<=l&&r<=y)return apply(i,v);
        int m=(l+r)/2;
        push(i);
        update(l,m,i*2,x,y,v);
        update(m,r,i*2+1,x,y,v);
        t.set(i,min(t.a[i*2],t.a[i*2+1]));
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<=l||r<=x)return INF;
        if(x<=l&&r<=y)return t.a[i];
        int m=(l+r)/2;
        push(i);
        return min(query(l,m,i*2,x,y),query(m,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
    void rollback(int x){
        t.rollback(x);
        lz.rollback(x);
    }
}

namespace Solver{
    vector<int> t[KK];
    void insert(int l,int r,int i,int x,int y,int id){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return void(t[i].emplace_back(id));
        int m=(l+r)/2;
        insert(l,m,i*2,x,y,id);
        insert(m+1,r,i*2+1,x,y,id);
    }
    void insert(int x,int y,int id){
        insert(1,q,1,x,y,id);
    }
    void solve(int l,int r,int i){
        int cur=Segtree::timer++;
        for(auto j:t[i]){
            Segtree::update(a[j].l,a[j].r,a[j].h);
        }
        if(l==r){
            if(qr[l].l>0&&qr[l].l<=qr[l].r){
                ans[l]=Segtree::query(qr[l].l,qr[l].r);
            }
        }else{
            int m=(l+r)/2;
            solve(l,m,i*2);
            solve(m+1,r,i*2+1);
        }
        Segtree::rollback(cur);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> op[i];
        if(op[i]=='+'){
            m++;
            cin >> a[m].l >> a[m].r >> a[m].h;
            st[m]=i;
            ed[m]=q;
            vals.emplace_back(a[m].l);
            vals.emplace_back(a[m].r);
        }else if(op[i]=='-'){
            int x;
            cin >> x;
            ed[x]=i;
        }else{
            cin >> qr[i].l >> qr[i].r;
            vals.emplace_back(qr[i].l);
            vals.emplace_back(qr[i].r);
        }
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    n=vals.size();
    for(int i=1;i<=q;i++){
        if(op[i]=='?'){
            qr[i].l=lower_bound(vals.begin(),vals.end(),qr[i].l)-vals.begin()+1;
            qr[i].r=lower_bound(vals.begin(),vals.end(),qr[i].r)-vals.begin()+1;
        }
    }
    for(int i=1;i<=m;i++){
        a[i].l=lower_bound(vals.begin(),vals.end(),a[i].l)-vals.begin()+1;
        a[i].r=lower_bound(vals.begin(),vals.end(),a[i].r)-vals.begin()+1;
        Solver::insert(st[i],ed[i],i);
    }
    Solver::solve(1,q,1);
    for(int i=1;i<=q;i++){
        if(op[i]=='?'){
            cout << ans[i] << "\n";
        }
    }
}