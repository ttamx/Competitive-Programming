#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int K=1<<19;
const int MOD=1e9+7;
const int BASE=101;

int n,q;
string s;
ll pw[N];

struct Info{
    int c0,c1,p,s;
    ll hsh;
    friend Info operator+(const Info &l,const Info &r){
        if(l.c0+l.c1==0)return r;
        if(r.c0+r.c1==0)return l;
        Info res{l.c0+r.c0,l.c1+r.c1,l.p,r.s,(l.hsh+r.hsh*pw[l.c0])%MOD};
        if(l.c0==0&&r.c0==0)return res;
        if(l.c0==0){
            res.p=(l.c1^r.p)&1;
        }else if(r.c0==0){
            res.s=(r.c1^l.s)&1;
        }else if(l.s^r.p){
            res.hsh=(res.hsh+pw[l.c0])%MOD;
        }
        return res;
    }
    friend bool operator==(const Info &l,const Info &r){
        return l.c0==r.c0&&l.c1==r.c1&&l.p==r.p&&l.s==r.s&&l.hsh==r.hsh;
    }
};

struct Segtree{
    Info t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=(s[l]=='1'?Info{0,1,1,1,0}:Info{1,0,0,0,0}));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(0,n-1,1);
    }
    Info query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return Info{0,0,0,0,0};
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
    Info query(int x,int y){
        return query(0,n-1,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s >> q;
    pw[0]=1;
    for(int i=1;i<=n;i++)pw[i]=pw[i-1]*BASE%MOD;
    seg.build();
    while(q--){
        int x,y,len;
        cin >> x >> y >> len;
        x--,y--,len--;
        cout << (seg.query(x,x+len)==seg.query(y,y+len)?"Yes":"No") << "\n";
    }
}