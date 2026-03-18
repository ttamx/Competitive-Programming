#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=55;
const int K=20;

int n,m;
int a[N];
ll dp[K][N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    m-=2;
    for(int i=1;i<=n;i++)cin >> a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++)for(int j=i+1;j<=n;j++)dp[0][i][j]=1;
    for(int c=1;c<=m;c++){
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                for(int k=j+1;k<=n;k++){
                    if(a[k]<=a[i]+a[j]){
                        dp[c][j][k]+=dp[c-1][i][j];
                    }
                }
            }
        }
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            ans+=dp[m][i][j];
        }
    }
    cout << ans << "\n";
}