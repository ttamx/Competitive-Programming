#include<bits/stdc++.h>

using namespace std;

const int N=105;

int n,m,ans;
char a[N][N];

bool valid(int i,int j){
    return 1<=i&&i<=n&&1<=j&&j<=m&&a[i][j]=='.';
}
void go(int x,int y){
    if(!valid(x,y))return;
    a[x][y]='#';
    for(int i=-1;i<=1;i++)for(int j=-1;j<=1;j++)go(x+i,y+j);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> a[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)if(valid(i,j))ans++,go(i,j);
    cout << ans;
}