#include<bits/stdc++.h>
 
using namespace std;

using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const int N=2e5+5;

int n,k;
ll a[N];
int root;
int l[N],r[N];

struct Treap{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val;
        int sz,prio;
        Ptr l,r;
        Node(ll v):val(v),sz(1),prio(rng()),l(),r(){}
    };
    Ptr root;
    Treap():root(){}
    int sz(Ptr t){
        return t?t->sz:0;
    }
    void pull(Ptr t){
        if(!t)return;
        t->sz=1+sz(t->l)+sz(t->r);
    }
    void merge(Ptr &t,Ptr l,Ptr r){
        if(!l)return void(t=r);
        if(!r)return void(t=l);
        if(l->prio>r->prio)merge(l->r,l->r,r),t=l;
        else merge(r->l,l,r->l),t=r;
        pull(t);
    }
    void split(Ptr t,Ptr &l,Ptr &r,ll key){
        if(!t)return void(l=r=nullptr);
        if(t->val<key)split(t->r,t->r,r,key),l=t;
        else split(t->l,l,t->l,key),r=t;
        pull(t);
    }
    void insert(ll v){
        Ptr t1,t2;
        split(root,t1,t2,v);
        merge(root,t1,new Node(v));
        merge(root,root,t2);
    }
    int query(ll v){
        Ptr t1,t2;
        split(root,t1,t2,v);
        int res=sz(t2);
        merge(root,t1,t2);
        return res;
    }
    template<class F>
    void iterate(const F &f){
        function<void(Ptr)> dfs=[&](Ptr t){
            if(!t)return;
            dfs(t->l);
            f(t->val);
            dfs(t->r);
        };
        dfs(root);
    }
};

struct DS{
    ll lz;
    Treap dat;
    DS():dat(),lz(0LL){}
    void insert(ll x){
        dat.insert(x-lz);
    }
    void add(ll x){
        lz+=x;
    }
    int query(ll x){
        return dat.query(-x-lz);
    }
    template<class F>
    void iterate(const F &f){
        dat.iterate([&](ll v){f(v+lz);});
    }
}pre[N],suf[N];

ll sum[N];
int sz[N];
ll ans=0;

void dfs(int u){
    if(!u)return;
    dfs(l[u]);
    dfs(r[u]);
    sum[u]=a[u]+sum[l[u]]+sum[r[u]];
    sz[u]=1+sz[l[u]]+sz[r[u]];
    ll cur=-k*a[u];
    if(a[u]>=0){
        if(a[u]==0)ans++;
        if(l[u]){
            ans+=suf[l[u]].query(cur);
        }
        if(r[u]){
            ans+=pre[r[u]].query(cur);
        }
        if(l[u]&&r[u]){
            if(sz[l[u]]<sz[r[u]]){
                suf[l[u]].iterate([&](ll v){
                    ans+=pre[r[u]].query(v+cur);
                });
            }else{
                pre[r[u]].iterate([&](ll v){
                    ans+=suf[l[u]].query(v+cur);
                });
            }
        }
    }\
    if(l[u]&&r[u]){
        suf[l[u]].add(sum[r[u]]+a[u]);
        pre[r[u]].add(sum[l[u]]+a[u]);
        if(sz[l[u]]<sz[r[u]]){
            swap(pre[u],pre[r[u]]);
            swap(suf[u],suf[r[u]]);
            pre[l[u]].iterate([&](ll v){
                pre[u].insert(v);
            });
            suf[l[u]].iterate([&](ll v){
                suf[u].insert(v);
            });
        }else{
            swap(pre[u],pre[l[u]]);
            swap(suf[u],suf[l[u]]);
            pre[r[u]].iterate([&](ll v){
                pre[u].insert(v);
            });
            suf[r[u]].iterate([&](ll v){
                suf[u].insert(v);
            });
        }
    }else if(l[u]){
        suf[l[u]].add(a[u]);
        swap(pre[u],pre[l[u]]);
        swap(suf[u],suf[l[u]]);
    }else if(r[u]){
        pre[r[u]].add(a[u]);
        swap(pre[u],pre[r[u]]);
        swap(suf[u],suf[r[u]]);
    }
    pre[u].insert(a[u]+sum[l[u]]);
    suf[u].insert(a[u]+sum[r[u]]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        ll x;
        cin >> x;
        a[i]-=x;
        if(a[i]<0)a[i]*=k;
    }
    vector<int> s;
    for(int i=1;i<=n;i++){
        while(!s.empty()&&a[s.back()]<a[i]){
            l[i]=s.back();
            s.pop_back();
        }
        (s.empty()?root:r[s.back()])=i;
        s.emplace_back(i);
    }
    dfs(root);
    cout << ans << "\n";
}