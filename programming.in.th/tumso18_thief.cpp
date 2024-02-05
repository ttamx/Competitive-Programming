#include<bits/stdc++.h>

using namespace std;

const int INF=INT_MAX/2;

const int N=1255;
const int K=1<<12;

int n,m,sx,sy;
int a[N*N];
int dp[N*N];
bool vis1[2*N][K],vis2[2*N][K];
queue<int> q;

int encode(int x,int y){
    return x*m+y;
}

void go(int v,int d){
    if(++d>=dp[v])return;
    q.emplace(v);
    dp[v]=d;
}

void trav1(int l,int r,int i,int d,int x,int y,int dist){
    if(y<l||r<x||vis1[d][i])return;
    if(x<=l&&r<=y){
        vis1[d][i]=true;
        for(int x=l;x<=r;x++)if(0<=d-x&&d-x<m)go(encode(x,d-x),dist);
        return;
    }
    int m=(l+r)/2;
    trav1(l,m,i*2,d,x,y,dist);
    trav1(m+1,r,i*2+1,d,x,y,dist);
}

void trav1(int d,int x,int y,int dist){
    if(d<0||n+m<d)return;
    trav1(0,n-1,1,d,x,y,dist);
}

void trav2(int l,int r,int i,int d,int x,int y,int dist){
    if(y<l||r<x||vis2[d][i])return;
    if(x<=l&&r<=y){
        vis2[d][i]=true;
        for(int x=l;x<=r;x++)if(0<=x-d+N&&x-d+N<m)go(encode(x,x-d+N),dist);
        return;
    }
    int m=(l+r)/2;
    trav2(l,m,i*2,d,x,y,dist);
    trav2(m+1,r,i*2+1,d,x,y,dist);
}

void trav2(int d,int x,int y,int dist){
    if(d<-m||n<d)return;
    trav2(0,n-1,1,d+N,x,y,dist);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> sx >> sy;
    for(int i=0;i<n*m;i++)dp[i]=INF;
    for(int i=0;i<n;i++)for(int j=0;j<m;j++){
        int u=encode(i,j);
        cin >> a[u];
        if(i==0||i==n-1||j==0||j==m-1)go(u,0);
    }
    int s=encode(sx-1,sy-1);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        int d=dp[u];
        if(u==s)cout << d,exit(0);
        int i=u/m,j=u%m,x=a[u];
        if(x>0){
            go(encode(x/m-1,x%m),d);
        }else{
            x=-x;
            trav1(i+j-x,i-x,i,d);
            trav1(i+j+x,i,i+x,d);
            trav2(i-j-x,i-x,i,d);
            trav2(i-j+x,i,i+x,d);
        }
    }
    cout << -1;
}