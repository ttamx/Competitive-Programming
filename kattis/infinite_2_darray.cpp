#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

const int N=2e6+5;

int x,y;
int fac[N],ifac[N];
int fib[N];

int modpow(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=1LL*res*a%MOD;
        a=1LL*a*a%MOD;
        b>>=1;
    }
    return res;
}

int C(int n,int r){
    return 1LL*fac[n]*ifac[r]%MOD*ifac[n-r]%MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    fac[0]=1;
    for(int i=1;i<N;i++)fac[i]=1LL*fac[i-1]*i%MOD;
    ifac[N-1]=modpow(fac[N-1],MOD-2);
    for(int i=N-1;i>=1;i--)ifac[i-1]=1LL*ifac[i]*i%MOD;
    cin >> x >> y;
    fib[1]=1;
    for(int i=2;i<N;i++)fib[i]=(fib[i-1]+fib[i-2])%MOD;
    int ans=0;
    for(int i=1;i<=x;i++){
        ans+=1LL*fib[i]*C(x-i+y-1,y-1)%MOD;
        ans%=MOD;
    }
    for(int i=1;i<=y;i++){
        ans+=1LL*fib[i]*C(y-i+x-1,x-1)%MOD;
        ans%=MOD;
    }
    cout << ans;
}