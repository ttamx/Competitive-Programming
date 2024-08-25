#include "cheat.h"
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

bool start=false;

int n,timer=0;
int p[N],sz[N],a[N];

int fp(int u){
    return u==p[u]?u:fp(p[u]);
}

int dep(int u){
    return u==p[u]?0:(dep(p[u])+1);
}

void init(){
    start=true;
    n=200000;
    for(int i=1;i<=n;i++){
        p[i]=i;
        sz[i]=1;
    }
}

void cheat(int u,int v){
    if(!start)init();
    ++timer;
    u=fp(u),v=fp(v);
    if(u==v)return;
    if(sz[u]<sz[v])swap(u,v);
    a[v]=timer;
    p[v]=u;
    sz[u]+=sz[v];
}

int investigate(int u,int v){
    if(!start)init();
    if(fp(u)!=fp(v))return -1;
    int du=dep(u),dv=dep(v);
    int res=0;
    while(u!=v){
        if(du<dv){
            swap(u,v);
            swap(du,dv);
        }
        res=max(res,a[u]);
        u=p[u];
        du--;
    }
    return res;
}