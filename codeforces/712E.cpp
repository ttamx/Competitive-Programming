#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

int n,q;
double p[N];

struct Info{
    double sum,prod;
    friend Info operator+(const Info &l,const Info &r){
        return Info{l.sum+r.sum*l.prod,l.prod*r.prod};
    }
};

struct Segtree{
    Info t[K];
    void modify(int l,int r,int i,int x,Info v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        modify(l,m,i*2,x,v);
        modify(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void modify(int x,Info v){
        modify(1,n,1,x,v);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info{0.0,1.0};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Info query(int x,int y){
        return query(1,n,1,x,y);
    }
}seg;

void upd(int i){
    if(i<0||i>n)return;
    double v=(1.0-p[i])/p[i];
    seg.modify(i,Info{v,v});
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int a,b;
        cin >> a >> b;
        p[i]=double(a)/b;
    }
    for(int i=1;i<=n;i++){
        upd(i);
    }
    cout << fixed << setprecision(10);
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int i,a,b;
            cin >> i >> a >> b;
            p[i]=double(a)/b;
            upd(i);
            upd(i-1);
        }else{
            int l,r;
            cin >> l >> r;
            double res=1.0/(1.0+seg.query(l,r).sum);
            cout << (isnan(res)?0.0:res) << "\n";
        }
    }
}