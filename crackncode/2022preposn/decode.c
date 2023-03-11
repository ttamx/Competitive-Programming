#define __USE_MINGW_ANSI_STDIO 0
#include<stdio.h>

const long long mod=1e9+7;

char s[12];
long long dp[1000001][8],dp2[1000001][8];

void runcase(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<8;i++)printf("%lld ",dp[n][i]);
    printf("\n");
}

int main(){
    int t;
    scanf("%d%s",&t,s);
    int num=(s[0]-48)*2+s[1]-48;
    int n=1;
    for(int i=2;s[i]!='\0';i++,n++){
        num*=2;
        num+=s[i]-48;
        ++dp[0][num];
        dp[0][num]%=mod;
        num%=4;
    }
    for(int i=0;i<8;i++)dp2[0][i]=dp[0][i];
    int l=s[0]-48,r=s[n]-48;
    int ll=l*2+s[1]-48,rr=(s[n-1]-48)*2+r;
    for(int i=1;i<=1000000;i++){
        for(int j=0;j<8;j++)dp[i][j]=2*dp2[i-1][j];
        if(i%2==0){
            dp[i][rr*2+1]++;
            dp[i][4+ll]++;
            dp[i][r*4+2+l]++;
        }else{
            dp[i][rr*2]++;
            dp[i][ll]++;
            dp[i][r*4+l]++;
        }
        for(int j=0;j<8;j++)dp[i][j]%=mod;
        for(int j=0;j<8;j++)dp2[i][j]=dp2[i-1][j]+dp[i][j];
        dp2[i][rr*2+l]++;
        dp2[i][r*4+ll]++;
        for(int j=0;j<8;j++)dp2[i][j]%=mod;
    }
    while(t--)runcase();
}