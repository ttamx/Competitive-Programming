#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;

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
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        push(l,m,r,i);
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}seg;

map<int,pair<int,int>> dat;

void split(int i){
    auto it=dat.lower_bound(i);
    if(it->first==i)return;
    dat[i]=it->second;
    it->second.first=i+1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    for(int i=0;i<=n+1;i++){
        dat[i]={i,i};
    }
    while(q--){
        int op,l,r;
        cin >> op >> l >> r;
        if(op==1){
            int x;
            cin >> x;
            split(l-1),split(r);
            for(auto it=dat.lower_bound(l);it->first<=r;it=dat.erase(it)){
                int cr=it->first;
                auto [cl,cv]=it->second;
                seg.update(1,n,1,cl,cr,abs(x-cv));
            }
            dat[r]={l,x};
        }else{
            cout << seg.query(1,n,1,l,r) << "\n";
        }
    }
}