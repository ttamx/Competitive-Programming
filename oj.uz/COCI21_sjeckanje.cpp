#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int K=1<<19;
const ll inf=1e18;

int n,q;
ll a[N],d[N];

struct mat:array<array<ll,2>,2>{
    mat(ll x=0){
        for(int i=0;i<2;i++)for(int j=0;j<2;j++)(*this)[i][j]=x;
    }
    mat(ll a,ll b){
        (*this)[0][0]=a;
        (*this)[0][1]=0;
        (*this)[1][0]=b;
        (*this)[1][1]=-inf;
    }
    friend mat operator*(mat a,mat b){
        mat c(-inf);
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    c[i][j]=max(c[i][j],a[i][k]+b[k][j]);
                }
            }
        }
        return c;
    }
};

struct segtree{
    mat t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=mat((d[l]^d[l-1])<0?0:abs(d[l]),abs(d[l])));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]*t[i*2+1];
    }
    void build(){
        build(2,n,1);
    }
    void update(int l,int r,int i,int x){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=mat((d[l]^d[l-1])<0?0:abs(d[l]),abs(d[l])));
        int m=(l+r)/2;
        update(l,m,i*2,x);
        update(m+1,r,i*2+1,x);
        t[i]=t[i*2]*t[i*2+1];
    }
    void update(int x){
        update(2,n,1,x);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)d[i]=a[i]-a[i-1];
    s.build();
    while(q--){
        int l,r,x;
        cin >> l >> r >> x;
        d[l]+=x;
        d[r+1]-=x;
        s.update(l);
        s.update(l+1);
        s.update(r+1);
        s.update(r+2);
        cout << max(s.t[1][0][0],s.t[1][1][0]) << "\n";
    }
}