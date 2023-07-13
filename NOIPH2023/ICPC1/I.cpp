#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=1e9+7;

const int K=35;

struct matrix{
    ll m[5][5];
    matrix(){
        for(int i=0;i<5;i++)for(int j=0;j<5;j++)m[i][j]=0;
    }
    friend matrix operator*(matrix lhs,matrix rhs){
        matrix res;
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                for(int k=0;k<5;k++){
                    res.m[i][j]+=lhs.m[i][k]*rhs.m[k][j];
                    res.m[i][j]%=mod;
                }
            }
        }
        return res;
    }
}dp[K];

ll f[5]={1,1,1,2,2};
ll g[5]={3,4,5,7,9};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<5;i++)dp[0].m[i][i-1]=1;
    dp[0].m[0][4]=dp[0].m[4][4]=1;
    for(int i=1;i<K;i++)dp[i]=dp[i-1]*dp[i-1];
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        ll ans=0;
        if(n<=5){
            ans=g[n-1];
        }else{
            n-=4;
            matrix res;
            for(int i=0;i<5;i++)res.m[i][i]=1;
            for(int i=0;i<K;i++)if(n>>i&1)res=res*dp[i];
            for(int i=0;i<5;i++){
                for(int j=0;j<5;j++){
                    ans+=f[j]*res.m[j][i];
                    ans%=mod;
                }
            }
        }
        cout << ans << "\n";
    }
}