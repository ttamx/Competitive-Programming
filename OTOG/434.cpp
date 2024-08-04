#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<vector<int>> v(n+2,vector<int>(m+2,0));
    while(q--){
        int a,b,c,d,x;
        cin >> a >> b >> c >> d >> x;
        v[a][b]+=x;
        v[a][d+1]-=x;
        v[c+1][b]-=x;
        v[c+1][d+1]+=x;
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)v[i][j]+=v[i-1][j]+v[i][j-1]-v[i-1][j-1];
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cout << v[i][j] << " \n"[j==m];
}