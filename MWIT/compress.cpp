#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,r;
    cin >> n >> m >> r;
    vector<vector<int>> a(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> a[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)a[i][j]+=a[i-1][j]+a[i][j-1]-a[i-1][j-1];
    for(int i=r+1;i<=n-r;i++){
        for(int j=r+1;j<=m-r;j++){
            cout << a[i+r][j+r]-a[i-r-1][j+r]-a[i+r][j-r-1]+a[i-r-1][j-r-1] << ' ';
        }
        cout << '\n';
    }
}