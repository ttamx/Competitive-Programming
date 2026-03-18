#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int K=1<<20;
const int MOD=998244353;
const int INF=INT_MAX/2;

struct Segtree{
    int t[K];
    void build(int l,int r,int i){
        t[i]=-INF;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void modify(int l,int r,int i,int x,int v){
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        if(x<=m)modify(l,m,i*2,x,v);
        else modify(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    int query(int l,int r,int i,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        if(t[i*2]<k)return query(l,m,i*2,k);
        else return query(m+1,r,i*2+1,k);
    }
}seg;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

void fwht(vector<ll> &a){
    int n=(int)a.size();
    assert(n==(n&-n));
    for(int i=1;i<n;i<<=1){
        for(int j=0;j<n;j++){
            if(j&i){
                ll &u=a[j^i],&v=a[j];
                tie(u,v)=make_pair((u+v)%MOD,(u-v+MOD)%MOD);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k,m;
    cin >> n >> k >> m;
    vector<int> p(n+1),grundy(n+1);
    for(int i=1;i<=n;i++){
        cin >> p[i];
    }
    seg.build(0,n,1);
    seg.modify(0,n,1,0,0);
    for(int i=1;i<=n;i++){
        grundy[i]=seg.query(0,n,1,i-p[i]);
        seg.modify(0,n,1,grundy[i],i);
    }
    int s=n+1;
    while(s!=(s&-s))s++;
    vector<ll> f(s),g(s);
    for(int i=0;i<=n;i++){
        f[grundy[i]]++;
    }
    for(int i=0;i<=n;i++){
        if(i+k>n||grundy[i]==grundy[i+k]){
            g[grundy[i]]++;
        }
    }
    auto calc=[&](vector<ll> &a){
        fwht(a);
        for(auto &x:a)x=binpow(x,m);
        fwht(a);
        return a[0]*binpow(s,MOD-2)%MOD;
    };
    cout << (calc(f)-calc(g)+MOD)%MOD << "\n";
}