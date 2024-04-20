#include<bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops")

using namespace std;

const int N=105;
const int K=2520;

int m,n,h;
int a[N][N];
bool vis[N][N][K];
queue<tuple<int,int,int>> q;

void go(int i,int j,int d){
    if(i<0||i>=m||j<0||j>=n||vis[i][j][d%K]||a[i][j]==0||d%a[i][j])return;
    q.emplace(d,i,j);
    vis[i][j][d%K]=true;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=0;i<m;i++)for(int j=0;j<n;j++)cin >> a[i][j];
    h=(m-1)/2;
    for(int i=-1;i<=1;i++)go(h+i,0,1);
    while(!q.empty()){
        auto [d,i,j]=q.front();
        q.pop();
        if(i==h&&j==n-1)cout << d,exit(0);
        d++;
        go(i,j-1,d),go(i,j+1,d);
        if(i&1)j--;
        go(i-1,j,d),go(i-1,j+1,d);
        go(i+1,j,d),go(i+1,j+1,d);
    }
    cout << -1;
}