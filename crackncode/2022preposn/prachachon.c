#include<stdio.h>

void runcase(){
    char s[13];
    scanf("%s",s);
    int val=0;
    for(int i=1;i<13;i++){
        val+=(14-i)*(s[i-1]-48);
        val%=11;
    }
    if(s[12]-48==(11-val)%10)printf("Y\n");
    else printf("N\n");
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--)runcase();
}