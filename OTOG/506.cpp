#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int mod=1e9+7;

struct matrix:array<array<ll,3>,3>{
    matrix(){
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)(*this)[i][j]=0;
    }
    friend matrix operator*(matrix a,matrix b){
        matrix c;
        for(int i=0;i<3;i++)for(int j=0;j<3;j++)for(int k=0;k<3;k++)c[i][j]+=a[i][k]*b[k][j],c[i][j]%=mod;
        return c;
    }
    matrix operator^(ll n){
        matrix res;
        for(int i=0;i<3;i++)res[i][i]=1;
        for(matrix cur=*this;n>0;n/=2,cur=cur*cur)if(n&1)res=res*cur;
        return res;
    }
};

void solve(){
    ll a,b,c,d,e,f,n;
    cin >> a >> b >> c >> d >> e >> f >> n;
    matrix m;
    m[1][0]=m[2][1]=1;
    m[0][2]=c;
    m[1][2]=b;
    m[2][2]=a;
    m=m^n;
    cout << (d*m[0][0]+e*m[1][0]+f*m[2][0])%mod << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}