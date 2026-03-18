#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const int INF=INT_MAX/2;

int n,q;
int a[N];

struct Info{
    int mx,mn;
    friend Info operator+(Info l,Info r){
        return Info{max(l.mx,r.mx),min(l.mn,r.mn)};
    }
};

struct Segtree{
    Info t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=Info{a[l],a[l]});
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info{-INF,INF};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    string s;
    cin >> s;
    for(int i=0;i<n;i++){
        a[i+1]=a[i]+(s[i]=='P'?+1:-1);
    }
    seg.build(0,n,1);
    while(q--){
        int l,r;
        cin >> l >> r;
        auto res=seg.query(0,n,1,l-1,r);
        cout << res.mx-res.mn << "\n";
    }
}