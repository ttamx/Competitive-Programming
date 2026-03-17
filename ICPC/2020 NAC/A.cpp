#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int MOD=998244353;

int n,k;
int mob[N];
ll ans=0;

ll binpow(ll a,ll b){
    ll res=1;
    while(b>0){
        if(b&1)res=res*a%MOD;
        a=a*a%MOD;
        b>>=1;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    mob[1]=1;
    for(int i=1;i<=k;i++){
        for(int j=i*2;j<=k;j+=i){
            mob[j]-=mob[i];
        }
    }
    for(int d=1;d<=k;d++){
        ans=(ans+mob[d]*(binpow(1+2*(k/d),n)-1)+MOD)%MOD;
    }
    cout << (ans+1)%MOD << "\n";
}