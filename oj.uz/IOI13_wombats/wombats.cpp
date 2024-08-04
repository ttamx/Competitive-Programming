#include "wombats.h"
#include <bits/stdc++.h>

using namespace std;

const int N=5005;
const int M=205;
const int B=10;
const int K=1<<10;
const int INF=1e9;

int n,m,b;
int h[N][M],v[N][M];

struct Matrix:array<array<int,M>,M>{
    Matrix(){
        for(int i=0;i<M;i++)for(int j=0;j<M;j++)(*this)[i][j]=INF;
        for(int i=0;i<M;i++)(*this)[i][i]=0;
    }
    friend Matrix operator*(const Matrix &a,const Matrix &b){
        Matrix res;
        array<array<int,M>,M> opt;
        for(int i=1;i<=m;i++)opt[i][0]=1;
        for(int i=1;i<=m;i++)opt[m+1][i]=m;
        for(int i=m;i>=1;i--){
            for(int j=1;j<=m;j++){
                res[i][j]=INF;
                for(int k=opt[i][j-1];k<=opt[i+1][j];k++){
                    int val=a[i][k]+b[k][j];
                    if(val<res[i][j]){
                        res[i][j]=val;
                        opt[i][j]=k;
                    }
                }
            }
        }
        return res;
    }
};

Matrix get_one(int x){
    Matrix res;
    for(int i=1;i<=m;i++){
        res[i][i]=0;
        for(int j=i+1;j<=m;j++){
            res[i][j]=res[i][j-1]+h[x][j-1];
        }
        for(int j=i-1;j>=1;j--){
            res[i][j]=res[i][j+1]+h[x][j];
        }
    }
    for(int i=1;i<=m;i++){
        for(int j=1;j<=m;j++){
            res[i][j]+=v[x][j];
        }
    }
    return res;
}

Matrix get_range(int x){
    int l=(x-1)*B+1,r=min(x*B,n);
    Matrix res=get_one(l);
    for(int i=l+1;i<=r;i++)res=res*get_one(i);
    return res;
}

struct SegTree{
    Matrix t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=get_range(l));
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]*t[i*2+1];
    }
    void build(){
        build(1,b,1);
    }
    void update(int l,int r,int i,int x){
        if(l==r)return void(t[i]=get_range(x));
        int m=(l+r)/2;
        if(x<=m)update(l,m,i*2,x);
        else update(m+1,r,i*2+1,x);
        t[i]=t[i*2]*t[i*2+1];
    }
    void update(int x){
        update(1,b,1,x);
    }
}s;

void init(int _n,int _m,int _h[5000][200],int _v[5000][200]){
    n=_n,m=_m,b=(n-1)/B+1;
    for(int i=1;i<=n;i++)for(int j=1;j<=m-1;j++)h[i][j]=_h[i-1][j-1];
    for(int i=1;i<=n-1;i++)for(int j=1;j<=m;j++)v[i][j]=_v[i-1][j-1];
    s.build();
}

void changeH(int i,int j,int x){
    h[i+1][j+1]=x;
    s.update(i/B+1);
}

void changeV(int i,int j,int x){
    v[i+1][j+1]=x;
    s.update(i/B+1);
}

int escape(int i,int j){
    return s.t[1][i+1][j+1];
}