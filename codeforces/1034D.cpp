#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=300005;
const int K=1<<20;
const int L=1e9;

int n,k;
int l[N],r[N];
ll a[N];
vector<tuple<int,int,int>> event[N];

struct Segtree{
    ll t[K],lz[K];
    void apply(int l,int r,int i,ll v){
        t[i]+=v*(r-l+1);
        lz[i]+=v;
    }
    void push(int l,int m,int r,int i){
        apply(l,m,i*2,lz[i]);
        apply(m+1,r,i*2+1,lz[i]);
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(l,r,i,v);
        int m=(l+r)/2;
        push(l,m,r,i);
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0LL;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    ll query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

struct Chtholly{
    map<int,pair<int,int>> dat;
    Chtholly(){dat[1e9]={-1e9,0};}
    template<class F>
    void enumerate(int l,int r,int v,const F &f){
        auto it=dat.upper_bound(l);
        {
            auto &[p,v]=it->second;
            if(p<l){
                dat[l]={p,v};
                p=l;
            }
        }
        for(;it!=dat.end()&&it->first<=r;it=dat.erase(it)){
            f(it->second.first,it->first,it->second.second);
        }
        if(it!=dat.end()){
            auto &[p,v]=it->second;
            if(p<r){
                f(p,r,v);
                p=r;
            }
        }
        dat[r]={l,v};
    }
}ds;

void prepare(){
    for(int i=1;i<=n;i++){
        ds.enumerate(l[i],r[i],i,[&](int l,int r,int j){
            if(j)event[i].emplace_back(1,j,-(r-l));
        });
        event[i].emplace_back(1,i,r[i]-l[i]);
    }
}

pair<ll,ll> solve(ll mid,bool f){
    ll sum=0,cnt=0;
    ll sz=0;
    for(int i=1;i<=n;i++)a[i]=0;
    for(int i=1,p=1;i<=n;i++){
        for(auto [l,r,v]:event[i]){
            if(r>=p)sz+=v;
            a[r]+=v;
            if(f)seg.update(l,r,v);
        }
        while(sz>=mid)sz-=a[p++];
        if(p>1){
            if(f)sum+=seg.query(1,p-1);
            cnt+=p-1;
        }
    }
    return {sum,cnt};
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> l[i] >> r[i];
    prepare();
    ll l=1,r=L;
    while(l<r){
        ll m=(l+r+1)/2;
        if(solve(m,false).second>=k)l=m;
        else r=m-1;
    }
    auto [sum,cnt]=solve(l,true);
    cout << sum-(cnt-k)*l << "\n";
}