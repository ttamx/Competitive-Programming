#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;

int n,m,q;
ll dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> dp[i][j];
            dp[i][j]+=dp[i][j-1]+dp[i-1][j]-dp[i-1][j-1];
        }
    }
    while(q--){
        int a,b,c,d;
        ll e;
        cin >> a >> b >> c >> d >> e;
        c++,d++;
        if(dp[c][d]-dp[c][b]-dp[a][d]+dp[a][b]<=e)cout << "Y\n";
        else cout << "N\n";
    }
}