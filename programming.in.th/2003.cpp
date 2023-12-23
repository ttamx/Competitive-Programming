#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,ans;
string s;
int mp[100];
int dp[2][4][4][4][4];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> s;
    mp['M']=1,mp['F']=2,mp['B']=3;
    for(int i=0;i<=1;i++)for(int j1=0;j1<=3;j1++)for(int j2=0;j2<=3;j2++)for(int k1=0;k1<=3;k1++)for(int k2=0;k2<=3;k2++)dp[i][j1][j2][k1][k2]=-2e9;
    dp[0][0][0][0][0]=0;
    for(int i=1;i<=n;i++){
        int x=mp[s[i-1]];
        for(int j1=0;j1<=3;j1++){
            for(int j2=0;j2<=3;j2++){
                for(int k1=0;k1<=3;k1++){
                    for(int k2=0;k2<=3;k2++){
                        int cnt=1;
                        if(k2==0){
                            cnt=1;
                        }else if(k1==0){
                            if(k2!=x)cnt=2;
                            else cnt=1;
                        }else if(k1!=k2){
                            if(k1!=x&&k2!=x)cnt=3;
                            else cnt=2;
                        }else if(k1!=x){
                            cnt=2;
                        }else{
                            cnt=1;
                        }
                        dp[i&1][j1][j2][k2][x]=max(dp[i&1][j1][j2][k2][x],dp[i&1^1][j1][j2][k1][k2]+cnt);
                        dp[i&1][k2][x][j1][j2]=max(dp[i&1][k2][x][j1][j2],dp[i&1^1][k1][k2][j1][j2]+cnt);
                    }
                }
            }
        }
    }
    for(int j1=0;j1<=3;j1++)for(int j2=0;j2<=3;j2++)for(int k1=0;k1<=3;k1++)for(int k2=0;k2<=3;k2++)ans=max(ans,dp[n&1][j1][j2][k1][k2]);
    cout << ans;
}