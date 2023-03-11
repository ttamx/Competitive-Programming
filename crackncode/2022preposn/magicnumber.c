#define __USE_MINGW_ANSI_STDIO 0
#include<stdio.h>

int sieve[16000000];
long long prime[1000001];
int cnt=1;

void runcase(){
    int n;
    scanf("%d",&n);
    printf("%lld\n",prime[n]);
}

int main(){
    for(long long i=2;cnt<=1000000;i++){
        if(sieve[i])continue;
        prime[cnt++]=i*i;
        for(int j=i;j<16000000;j+=i)sieve[j]=1;
    }
    int t;
    scanf("%d",&t);
    while(t--)runcase();
}