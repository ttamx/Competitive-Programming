#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e6+5;
const int A=21;

int n;
int a[N];
int dp[N][A];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]--;
    }
    for(int i=1;i<=n;i++){
        int mx=0;
        for(int j=A-1;j>=0;j--){
            if(j!=a[i]){
                dp[i][j]=dp[i-1][j];
            }else{
                dp[i][j]=mx+1;
            }
            mx=max(mx,dp[i-1][j]);
        }
        if(i>1){
            for(int j=A-1;j>=0;j--){
                if(j!=a[i]){
                    dp[i][j]=min(dp[i][j],dp[i-2][j]);
                }else{
                    dp[i][j]=min(dp[i][j],mx+1);
                }
                mx=max(mx,dp[i-2][j]);
            }
        }
    }
    cout << min(*max_element(dp[n-1],dp[n-1]+A),*max_element(dp[n],dp[n]+A)) << "\n";
}