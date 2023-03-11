#define __USE_MINGW_ANSI_STDIO 0
#include<stdio.h>

int dp[100001];
int a[10]={0,1,-1,-1,-1,-1,9,-1,8,6};
int ans[1000001];

int main(){
    for(int i=1;i<=100000;i++){
        dp[i]=dp[i-1];
        int res=i;
        int ok=1;
        int num=1;
        while(res/num>9)num*=10;
        while(res>0){
            int x=res;
            x=res/num;
            if(a[x]!=res%10){
                ok=0;
                break;
            }
            res%=num;
            res/=10;
            num/=100;
        }
        dp[i]+=ok;
    }
    int t;
    scanf("%d",&t);
    for(int i=0;i<t;i++){
        int l,r;
        scanf("%d%d",&l,&r);
        ans[i]=dp[r]-dp[l-1];
    }
    for(int i=0;i<t;i++){
        printf("%d\n",ans[i]);
    }
}