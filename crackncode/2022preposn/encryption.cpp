#include<stdio.h>

void runcase(){
    long long n;
    scanf("%lld",&n);
    long long ans=0,res=0;
    while(n){
        if(n&1){
            res*=2;
            res++;
        }else{
            ans+=res;
            res=0;
        }
        n/=2;
    }
    ans+=res;
    printf("%lld\n",ans);
}

int main(){
    int t=5;
    while(t--)runcase();
}