#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=1<<20;
const int INF=1e9;

int n;
int a[N],b[N],h[N],w[N];
int idx[N];
vector<pair<int,int>> event[N];

struct SegTree{
    struct Node{
        int val,cnt;
        Node():val(-INF),cnt(0){}
        Node(int _val):val(_val),cnt(1){}
        Node(int _val,int _cnt):val(_val),cnt(_cnt){}
        friend Node operator+(const Node &lhs,const Node &rhs){
            if(lhs.val>rhs.val)return lhs;
            if(lhs.val<rhs.val)return rhs;
            return Node(lhs.val,lhs.cnt+rhs.cnt);
        }
    }t[K];
    int lz[K];
    void push(int l,int r,int i){
        t[i].val+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Node(-INF));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void modify(int l,int r,int i,int x,Node v){
        push(l,r,i);
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=Node(v));
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,Node v){
        modify(1,n,1,x,v);
    }
    void update(int l,int r,int i,int x,int y,int v){
        push(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]+=v,push(l,r,i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,int v){
        update(1,n,1,x,y,v);
    }
    Node query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return Node();
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Node query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i){
            t[i]+=v;
        }
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
}fen;

void update(int i,int v){
    if(w[i]==0){
        seg.modify(i,SegTree::Node(fen.query(i-1)*2-idx[i]));
    }
    seg.update(i,n,v*2);
    fen.update(i,v);
    w[i]+=v;
    if(w[i]==0){
        seg.modify(i,SegTree::Node(-INF));
    }
}

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        h[i]=a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    sort(b+1,b+n+1);
    sort(h+1,h+n+1);
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(h+1,h+n+1,a[i])-h;
    }
    for(int i=1;i<=n;i++){
        int j=upper_bound(b+1,b+n+1,h[i])-b-1;
        if(h[i]==b[j]){
            idx[i]=j*2;
        }else{
            idx[i]=j*2+1;
        }
    }
    seg.build();
    {
        vector<pair<int,int>> s;
        for(int i=1;i<=n;i++){
            int cur=1;
            while(!s.empty()&&s.back().first>=a[i]){
                auto [h,w]=s.back();
                s.pop_back();
                event[i].emplace_back(h,-w);
                cur+=w;
            }
            event[i].emplace_back(a[i],cur);
            s.emplace_back(a[i],cur);
        }
    }
    {
        vector<pair<int,int>> s;
        for(int i=n;i>=1;i--){
            int cur=1;
            while(!s.empty()&&s.back().first>=a[i]){
                auto [h,w]=s.back();
                s.pop_back();
                event[i+1].emplace_back(h,w);
                cur+=w;
            }
            event[i+1].emplace_back(a[i],-cur);
            s.emplace_back(a[i],cur);
        }
        for(auto [h,w]:s){
            update(h,w);
        }
    }
    int ans=n+1;
    for(int i=1;i<=n;i++){
        for(auto [h,w]:event[i]){
            update(h,w);
        }
        update(a[i],-1);
        auto res=seg.t[1];
        if(res.val==0){
            ans=min(ans,res.cnt);
        }else if(res.val<0){
            ans=0;
        }
        update(a[i],+1);
    }
    cout << (ans>n?-1:ans);
}