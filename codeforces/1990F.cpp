#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max-idx.hpp"

struct Interval{
    int l,r;
    Interval(int _l,int _r):l(_l),r(_r){}
    bool contains(int x){
        return l<=x&&x<=r;
    }
};

struct IntervalTree{
    struct CmpL{
        bool operator()(const Interval &x,const Interval &y)const{
            return x.l<y.l||(x.l==y.l&&x.r<y.r);
        }
    };
    struct CmpR{
        bool operator()(const Interval &x,const Interval &y)const{
            return x.r>y.r||(x.r==y.r&&x.l>y.l);
        }
    };
    struct Container{
        multiset<Interval,CmpL> sl;
        multiset<Interval,CmpR> sr;
        Container():sl(),sr(){}
        void erase(const Interval &x){
            sl.erase(sl.find(x));
            sr.erase(sr.find(x));
        }
        void insert(const Interval &x){
            sl.emplace(x);
            sr.emplace(x);
        }
        void query_left(int x,vector<Interval> &res){
            while(!sl.empty()&&sl.begin()->l<=x){
                auto v=*sl.begin();
                res.emplace_back(v);
                erase(v);
            }
        }
        void query_right(int x,vector<Interval> &res){
            while(!sr.empty()&&sr.begin()->r>=x){
                auto v=*sr.begin();
                res.emplace_back(v);
                erase(v);
            }
        }
    };
    int n;
    vector<Container> t;
    IntervalTree(int _n):n(_n){
        int sz=1;
        while(sz<2*n)sz<<=1;
        t.assign(sz,Container());
    }
    void insert(int l,int r,int i,Interval v){
        if(l>r)return;
        int m=(l+r)/2;
        if(v.contains(m))return t[i].insert(v);
        if(v.r<m)insert(l,m-1,i*2,v);
        if(v.l>m)insert(m+1,r,i*2+1,v);
    }
    void insert(Interval v){
        insert(0,n-1,1,v);
    }
    void query(int l,int r,int i,int x,vector<Interval> &res){
        if(l>r||x<l||r<x)return;
        int m=(l+r)/2;
        if(x<=m)t[i].query_left(x,res);
        if(x>=m)t[i].query_right(x,res);
        query(l,m-1,i*2,x,res);
        query(m+1,r,i*2+1,x,res);
    }
    vector<Interval> query(int x){
        vector<Interval> res;
        query(0,n-1,1,x,res);
        return res;
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<ll> a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    Fenwick<ll> fen(a);
    vector<pair<ll,int>> dat(n+2);
    for(int i=0;i<n+2;i++)dat[i]={a[i],i};
    SegmentTree<MaxIdxMonoid<ll>> seg(dat);
    IntervalTree ranges(n+2);
    map<pair<int,int>,int> dp;
    function<int(int,int)> solve=[&](int l,int r){
        if(r-l<2)return -1;
        if(dp.count({l-1,r+1}))return dp[{l-1,r+1}];
        auto [mx,id]=seg.query(l,r);
        if(mx*2<fen.query(l,r))return r-l+1;
        ranges.insert(Interval(l-1,r+1));
        return dp[{l-1,r+1}]=max(solve(l,id-1),solve(id+1,r));
    };
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int l,r;
            cin >> l >> r;
            cout << solve(l,r) << "\n";
        }else{
            int x;
            ll v;
            cin >> x >> v;
            seg.modify(x,{v,x});
            fen.update(x,v-a[x]);
            a[x]=v;
            for(auto range:ranges.query(x))dp.erase({range.l,range.r});
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}