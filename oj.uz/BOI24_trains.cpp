#include <bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=224;
const int MOD=1e9+7;

int n;
int d[N],x[N];
int dp[N],add[N][K];
int ans;

void norm(int &x){
    if(x<0)x+=MOD;
    if(x>=MOD)x-=MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> d[i] >> x[i];
    dp[1]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<K;j++){
            if(i-j>=0)norm(add[i][j]+=add[i-j][j]);
            norm(dp[i]+=add[i][j]);
        }
        if(d[i]<K){
            if(i+d[i]<=n)norm(add[i+d[i]][d[i]]+=dp[i]);
            if(i+1LL*d[i]*(x[i]+1)<=n)norm(add[i+d[i]*(x[i]+1)][d[i]]-=dp[i]);
        }else{
            for(int j=1;j<=x[i]&&i+1LL*j*d[i]<=n;j++){
                norm(dp[i+j*d[i]]+=dp[i]);
            }
        }
        norm(ans+=dp[i]);
    }
    cout << ans;
}