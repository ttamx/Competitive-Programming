#include<bits/stdc++.h>

using namespace std;

const int N=50005;
const int K=35;

int n,c,ans;
int a[N][K],dp[N][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> c;
    for(int i=0;i<c;i++){
        int e,f,l;
        cin >> e >> f >> l;
        int bf=0,bl=0;
        for(int j=0;j<f;j++){
            int x;
            cin >> x;
            if(x<e)x+=n;
            bf+=(1<<(x-e));
        }
        for(int j=0;j<l;j++){
            int x;
            cin >> x;
            if(x<e)x+=n;
            bl+=(1<<(x-e));
        }
        for(int j=0;j<32;j++){
            if((j&bf)!=0||(bl!=0&&(j&bl)!=bl)){
                a[e][j]++;
            }
        }
    }
    for(int st=0;st<32;st++){
        for(int j=0;j<32;j++)dp[0][j]=-2e9;
        dp[0][st]=0;
        for(int i=1;i<=n;i++){
            for(int j=0;j<32;j++){
                dp[i][j]=max(dp[i-1][(j&15)<<1],dp[i-1][(j&15)<<1|1])+a[i][j];
            }
        }
        ans=max(ans,dp[n][st]);
    }
    cout << ans;
}