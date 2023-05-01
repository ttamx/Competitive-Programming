#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=305;
const int M=1505;
const int K=605;
const ll mod=1e6+3;

int r,c,k,ans;
ll a[2][M][M];
ll fac[K],inv[K];

ll binpow(ll a,ll b){
    ll res=1;
    for(;b>0;b>>=1,a*=a,a%=mod)if(b&1)res*=a,res%=mod;
    return res;
}

ll C(int n,int r){
    if(r>n)return 0;
    return fac[n]*inv[n-r]%mod*inv[r]%mod;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c >> k;
    fac[0]=1;
    for(int i=1;i<=600;i++)fac[i]=fac[i-1]*i%mod;
    inv[600]=binpow(fac[600],mod-2);
    for(int i=600;i>0;i--)inv[i-1]=inv[i]*i%mod;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            char x;
            cin >> x;
            a[0][i+600][j+600]=a[1][i+600][j+600]=(x=='#');
        }
    }
    for(int i=1;i<M-1;i++)for(int j=1;j<M-1;j++)a[0][i][j]+=a[0][i-1][j-1],a[1][i][j]+=a[1][i-1][j+1];
    for(int l=1;l<=r+c;l++){
        for(int i=601;i<=r+600;i++){
            for(int j=601;j<=c+600;j++){
                int cnt=0;
                cnt+=a[0][i-1][j+l-1]-a[0][i-l-1][j-1];
                cnt+=a[0][i+l][j]-a[0][i][j-l];
                cnt+=a[1][i+l-1][j+1]-a[1][i-1][j+l+1];
                cnt+=a[1][i][j-l]-a[1][i-l][j];
                ans+=C(cnt,k),ans%=mod;
            }
        }
    }
    cout << ans;
}