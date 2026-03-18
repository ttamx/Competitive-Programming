#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Tag{
    int lz,h_lz;
    void apply(const Tag &o){
        h_lz=min(h_lz,lz+o.h_lz);
        lz+=o.h_lz;
    }
};

struct Info{
    int mn,h_mn;
    friend Info operator+(const Info &x,const Info &y){
        return Info{min(x.mn,y.mn),min(x.h_mn,y.h_mn)};
    }
    void apply(const Tag &o){
        h_mn=min(h_mn,mn+o.h_lz);
        mn+=o.lz;
    }
};

struct Segtree{
    vector<Info> t;
    vector<Tag> lz;
    Segtree(vector<int> &a){
        int n=a.size();
        t.resize(4*n);
        lz.resize(4*n,Tag{0,0});
        function<void(int,int,int)> build=[&](int l,int r,int i){
            if(l==r)return void(t[i]=Info{a[l],a[l]});
            int m=(l+r)/2;
            build(l,m,i*2);
            build(m+1,r,i*2+1);
            t[i]=t[i*2]+t[i*2+1];
        };
        build(0,n-1,1);
    }
    void apply(int i,Tag v){
        t[i].apply(v);
        lz[i].apply(v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=Tag{0,0};
    }
    void update(int l,int r,int i,int x,int y,Tag v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
};

void runcase(){
    
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}