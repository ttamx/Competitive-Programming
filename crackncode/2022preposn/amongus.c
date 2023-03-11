#include<stdio.h>

void runcase(){
    int n;
    scanf("%d",&n);
    if(n%4==1){
        int a=n/4+1,b=n/4+1,c=n-n/4,d=n-n/4;
        for(int i=0;i<=n/4;i++){
            for(int j=1;j<=n;j++){
                if((a<=j&&j<=b)||(c<=j&&j<=d))printf("#");
                else printf(".");
            }
            a--,b++,c--,d++;
            printf("\n");
        }
        for(int i=1;i<=n/2;i++){
            for(int j=1;j<=n;j++){
                if(j<=i||n-j<i)printf(".");
                else printf("#");
            }
            printf("\n");
        }
    }else{
        int a=n/4+1,b=n/4+2,c=n-n/4-1,d=n-n/4;
        for(int i=0;i<=n/4;i++){
            for(int j=1;j<=n;j++){
                if((a<=j&&j<=b)||(c<=j&&j<=d))printf("#");
                else printf(".");
            }
            a--,b++,c--,d++;
            printf("\n");
        }
        for(int i=1;i<=n/2;i++){
            for(int j=1;j<=n;j++){
                if(j<=i||n-j<i)printf(".");
                else printf("#");
            }
            printf("\n");
        }
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--)runcase();
}