#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n+2,vector<int>(m+2));
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            a[i][j+1]=(s[j]=='B');
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            a[i][j]^=a[i][j+1]^a[i+1][j]^a[i+1][j+1];
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ans+=a[i][j];
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(a[i][j]&&a[i][m]&&a[n][j]&&a[n][m]){
                cout << ans-1 << "\n";
                exit(0);
            }
        }
    }
    cout << ans << "\n";
}