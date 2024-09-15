#include <stdio.h>
#include <stdlib.h>
#define N 100005
#define INF 1000000000

struct Info{
    int key;
    int val;
};

int *to[N],*we[N];
int sz[N];

void append(int i,int _to,int _w){
    int x=sz[i]++;
    if(x>=2&&(x&x-1)==0){
        to[i]=(int*)realloc(to[i],x*2*sizeof*to[i]);
        we[i]=(int*)realloc(we[i],x*2*sizeof*we[i]);
    }
    to[i][x]=_to;
    we[i][x]=_w;
}

struct Info h[N];
int hsz;

void swap(int i,int j){
    struct Info e=h[i];
    h[i]=h[j];
    h[j]=e;
}

void up(int i){
    int p;
    for(;i>0;i=p){
        p=(i-1)/2;
        if(h[i].val<h[p].val){
            swap(i,p);
        }
    }
}

void down(){
    for(int i=0;h[i].val>h[i*2+1].val||h[i].val>h[i*2+2].val;){
        int j=(h[i*2+1].val<h[i*2+2].val)?(i*2+1):(i*2+2);
        swap(i,j);
        i=j;
    }
}

void push(struct Info v){
    h[hsz]=v;
    up(hsz);
    hsz++;
}

struct Info pop(){
    struct Info x=h[0];
    h[0].val=INF;
    swap(0,--hsz);
    down();
    return x;
}

struct Info dp[N];

int main(){
    int n,m,s,t;
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=0;i<n;i++){
        to[i]=(int*)malloc(2*sizeof*to[i]);
        we[i]=(int*)malloc(2*sizeof*we[i]);
    }
    for(int i=0;i<N;i++){
        h[i].val=INF;
    }
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        append(u,v,w);
        append(v,u,w);
    }
    for(int i=0;i<n;i++){
        dp[i].key=i;
        dp[i].val=INF;
    }
    dp[s].val=0;
    push(dp[s]);
    while(hsz>0){
        struct Info e=pop();
        int u=e.key;
        int d=e.val;
        if(d>dp[u].val){
            continue;
        }
        for(int i=0;i<sz[u];i++){
            int v=to[u][i],w=we[u][i];
            if(d+w<dp[v].val){
                dp[v].val=d+w;
                push(dp[v]);
            }
        }
    }
    printf("%d",dp[t].val);
}