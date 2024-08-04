#include<bits/stdc++.h>

using namespace std;

struct PersistSegTree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node():val(0),l(nullptr),r(nullptr){}
    };
    vector<Ptr> roots;
    int n;
    PersistSegTree(int n,int v):n(n),roots(v){}
    void build(int l,int r,Ptr &t){
        t=new Node();
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int cur){
        build(0,n-1,roots[cur]);
    }
    void update(int l,int r,Ptr &t,Ptr &o,int x,int v){
        t=new Node(*o);
        t->val+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,o->l,x,v);
        else update(m+1,r,t->r,o->r,x,v);
    }
    void update(int x,int v,int pre,int cur){
        update(0,n-1,roots[cur],roots[pre],x,v);
    }
    int query(int l,int r,Ptr &t,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    int query(int x,int y,int cur){
        return query(0,n-1,roots[cur],x,y);
    }
    int find(int l,int r,Ptr &t,int k){
        if(t->val<k)return n;
        if(l==r)return l;
        int m=(l+r)/2;
        if(t->l->val>=k)return find(l,m,t->l,k);
        else return find(m+1,r,t->r,k-t->l->val);
    }
    int find(int cur,int k){
        return find(0,n-1,roots[cur],k);
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int mx=*max_element(a.begin(),a.end());
    vector<vector<int>> pos(mx+1);
    for(int i=0;i<n;i++)pos[a[i]].emplace_back(i);
    PersistSegTree pst(n,mx+2);
    pst.build(mx+1);
    for(int i=mx;i>=1;i--){
        pst.roots[i]=pst.roots[i+1];
        for(auto x:pos[i]){
            pst.update(x,1,i,i);
        }
    }
    vector<vector<pair<int,int>>> qr(n+1);
    vector<bool> ans(q);
    for(int i=0;i<q;i++){
        int x,k;
        cin >> x >> k;
        x--;
        qr[k].emplace_back(x,i);
    }
    for(int k=1;k<=n;k++){
        sort(qr[k].rbegin(),qr[k].rend());
        int cur=0,lv=1;
        while(cur<n){
            int cnt=pst.query(0,cur-1,lv);
            int nxt=pst.find(lv,k+cnt);
            while(!qr[k].empty()&&qr[k].back().first<=nxt){
                auto [x,i]=qr[k].back();
                if(a[x]>=lv)ans[i]=true;
                qr[k].pop_back();
            }
            cur=nxt+1;
            lv++;
        }
    }
    for(auto x:ans)cout << (x?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}