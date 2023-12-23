#include "volunteers.h"
#include<bits/stdc++.h>

using namespace std;

const int N=20005;
const int M=405;
const int K=1<<16;
const int inf=1e9;

int n,m;
int h[N][M];
int dp[N][M],ans[N];
int pre[N],suf[N];

struct persist{
    struct node;
    typedef node* pnode;
    struct node{
        int val;
        pnode l,r;
        node(int x):val(x),l(nullptr),r(nullptr){}
    };
    pnode rt[N];
    void build(int l,int r,pnode &t){
        t=new node(0);
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,t->l);
        build(m+1,r,t->r);
    }
    void build(int cur){
        build(1,n,rt[cur]);
    }
    void update(int l,int r,pnode &t,int x,int v,pnode k){
        t=new node(*k);
        t->val=max(t->val,v);
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v,k->l);
        else update(m+1,r,t->r,x,v,k->r);
    }
    void update(int pre,int cur,int x,int v){
        update(1,n,rt[cur],x,v,rt[pre]);
    }
    int query(int l,int r,pnode &t,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return max(query(l,m,t->l,x,y),query(m+1,r,t->r,x,y));
    }
    int query(int cur,int x,int y){
        return query(1,n,rt[cur],x,y);
    }
}pst;

void setup_battalion(int N, int M, int Q, vector<vector<int>> H){
    n=N,m=M;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)h[i][j]=H[i-1][j-1];
        sort(h[i]+1,h[i]+m+1);
        h[i][m+1]=inf;
    }
    for(int i=0;i<=n+1;i++)suf[i]=inf;
    h[0][1]=inf;
    pst.build(0);
    for(int i=1;i<=n;i++){
        for(int j=1,k=1;j<=m;j++){
            while(h[i-1][k]<h[i][j])k++;
            dp[i][j]=dp[i-1][k]+1;
            ans[i]=max(ans[i],dp[i][j]);
        }
        int l=i-ans[i]+1;
        pst.update(i-1,i,l,ans[i]);
        pre[l]=max(pre[l],i);
        suf[i]=l;
    }
    for(int i=1;i<=n;i++)pre[i]=max(pre[i],pre[i-1]);
    for(int i=n;i>=1;i--)suf[i]=min(suf[i],suf[i+1]);
}

int count_volunteers(int L, int R){
    L++,R++;
    int ans=1;
    ans=max(ans,min(pre[L],R)-L+1);
    ans=max(ans,R-max(suf[R],L)+1);
    ans=max(ans,pst.query(R,L,R));
    return ans;
}