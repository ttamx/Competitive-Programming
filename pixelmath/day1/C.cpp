#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int M=1e5+5;
const int NM=6e5+5;
const int K=1<<20;
const int MOD=1e9+7;
const int INF=INT_MAX/2;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int n,m;
int c[N];
bool f[M];
ll fac[NM],ifac[NM];

struct segtree{
    ll mn[K],mx[K];
    void build(int l,int r,int i){
        if(l==r)return void(mn[i]=mx[i]=c[l]);
        int mid=(l+r)/2;
        build(l,mid,i*2);
        build(mid+1,r,i*2+1);
        mn[i]=min(mn[i*2],mn[i*2+1]);
        mx[i]=max(mx[i*2],mx[i*2+1]);
    }
    pair<int,int> query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return {INF,-INF};
        if(x<=l&&r<=y)return {mn[i],mx[i]};
        int mid=(l+r)/2;
        auto [mnl,mxl]=query(l,mid,i*2,x,y);
        auto [mnr,mxr]=query(mid+1,r,i*2+1,x,y);
        return {min(mnl,mnr),max(mxl,mxr)};
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    fac[0]=1;
    for(int i=1;i<=n+m;i++)fac[i]=fac[i-1]*i%MOD;
    ifac[n+m]=binpow(fac[n+m],MOD-2);
    for(int i=n+m;i>=1;i--)ifac[i-1]=ifac[i]*i%MOD;
    int s;
    cin >> s;
    while(s--){
        int x;
        cin >> x;
        f[x]=true;
    }
    vector<int> t(n);
    for(int i=0;i<n;i++){
        int g=gcd(i+1,n);
        cin >> c[i];
        if(g>1&&f[c[i]%m]){
            t[i]=0;
        }else if(g==1&&!f[c[i]%m]){
            t[i]=1;
        }else{
            t[i]=2;
        }
    }
    seg.build(0,n-1,1);
    vector<array<int,3>> a(n+1,{0,0,0});
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            a[i+1][j]=a[i][j]+(t[i]==j);
        }
    }
    int q;
    cin >> q;
    while(q--){
        int l,r,op;
        cin >> l >> r >> op;
        array<int,3> b{};
        for(int i=0;i<3;i++)b[i]=a[r][i]-a[l-1][i];
        auto [mn,mx]=seg.query(0,n-1,1,l-1,r-1);
        cout << b[0] << " " << b[1] << " " << b[2] << " " << mx-mn;
        if(op){
            int x=max({b[0],b[1],b[2]});
            cout << " " << fac[n+m]*ifac[x]%MOD*ifac[n+m-x]%MOD;
        }
        cout << "\n";
    }
}