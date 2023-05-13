#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;

const int N=10005;
const int M=105;

int n,d;
int a[N];
int dp[N][M][2];
string s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> s >> d;
    int n=s.size();
    for(int i=1;i<=n;i++)a[i]=s[i-1]-'0';
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<d;j++){
            for(int k=0;k<=9;k++){
                if(k<a[i]){
                    dp[i][j][1]+=dp[i-1][(j-k+10*d)%d][0]+dp[i-1][(j-k+10*d)%d][1];
                    dp[i][j][1]%=mod;
                }else if(k==a[i]){
                    dp[i][j][0]+=dp[i-1][(j-k+10*d)%d][0];
                    dp[i][j][0]%=mod;
                    dp[i][j][1]+=dp[i-1][(j-k+10*d)%d][1];
                    dp[i][j][1]%=mod;
                }else{
                    dp[i][j][1]+=dp[i-1][(j-k+10*d)%d][1];
                    dp[i][j][1]%=mod;
                }
            }
        }
    }
    cout << (dp[n][0][0]+dp[n][0][1]-1+mod)%mod;
}