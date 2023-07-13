#include<bits/stdc++.h>

using namespace std;

const int N=3005;
const int mod=1e9+7;

int n;
int dp[N][N];
string s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> s;
    for(int i=1;i<=n;i++)dp[0][i]=1;
    for(int i=1;i<n;i++){
        if(s[i-1]=='<'){
            int sum=0;
            for(int j=1;j<=n-i;j++){
                sum+=dp[i-1][j];
                if(sum>=mod)sum-=mod;
                dp[i][j]=sum;
            }
        }else{
            int sum=0;
            for(int j=n-i;j>=1;j--){
                sum+=dp[i-1][j+1];
                if(sum>=mod)sum-=mod;
                dp[i][j]=sum;
            }
        }
    }
    cout << dp[n-1][1];
}