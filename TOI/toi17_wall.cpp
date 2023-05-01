#include<bits/stdc++.h>

using namespace std;

const int N=1005;

int r,c,ans;
char a[N][N];

bool valid(int i,int j){
    return 0<=i&&i<=r+1&&0<=j&&j<=c+1;
}

void pre(int i,int j){
    if(!valid(i,j)||a[i][j]!='.')return;
    a[i][j]='W';
    pre(i+1,j);
    pre(i,j+1);
    pre(i-1,j);
    pre(i,j-1);
}

int dfs(int i,int j){
    if(!valid(i,j)||a[i][j]!='X')return 0;
    a[i][j]='.';
    return (a[i+1][j]=='W')+(a[i][j+1]=='W')+(a[i-1][j]=='W')+(a[i][j-1]=='W')+dfs(i+1,j)+dfs(i,j+1)+dfs(i-1,j)+dfs(i,j-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c;
    for(int i=0;i<=r+1;i++)a[i][0]=a[i][c+1]='.';
    for(int i=0;i<=c+1;i++)a[0][i]=a[r+1][i]='.';
    for(int i=1;i<=r;i++)for(int j=1;j<=c;j++)cin >> a[i][j];
    pre(0,0);
    for(int i=1;i<=r;i++)for(int j=1;j<=c;j++)ans=max(ans,dfs(i,j));
    cout << ans;
}