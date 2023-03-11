#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N=1e6+5;
const ll MOD=1e9+7;

int q;

struct A{
    ll a[4][4];
    friend A operator *(const A &a,const A &b){
        A c;
        for(int i=0;i<4;++i){
            for(int j=0;j<4;++j){
                c.a[i][j]=0;
                for(int k=0;k<4;++k){
                    c.a[i][j]+=a.a[i][k]*b.a[k][j];
                    c.a[i][j]%=MOD;
                }
            }
        }
        return c;
    }
}dp[60],I;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> q;
    dp[0].a[0][0]=1;
    dp[0].a[0][3]=1;
    dp[0].a[1][0]=2;
    dp[0].a[2][1]=1;
    dp[0].a[2][2]=1;
    dp[0].a[3][2]=2;
    for(int i=0;i<4;++i)I.a[i][i]=1;
    for(int i=1;i<60;++i)dp[i]=dp[i-1]*dp[i-1];
    while(q--){
        ll n;
        cin >> n;
        if(n==1){
            cout << 1 << '\n';
            continue;
        }
        --n;
        A ans=I;
        int i=0;
        while(n>0){
            if(n&1)ans=ans*dp[i];
            n>>=1;
            ++i;
        }
        cout << ((2ll*ans.a[0][2])+(2ll*ans.a[0][3])+ans.a[3][2]+ans.a[3][3])%MOD << "\n";
    }
}
