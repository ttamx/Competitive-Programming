#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+6;
const int T=15;
const int mod=1e9+7;

int n,m,t;
int a[T],b[T],c[T],d[T];
ll dp[2][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> t;
    for(int i=1;i<=t;i++)cin >> a[i] >> b[i] >> c[i] >> d[i];
    auto sol=[&](){
        dp[0][0]=1;
        for(int i=1;i<=n;i++)dp[0][i]=0;
        for(int i=1;i<=t;i++){
            int l=0,r=-1;
            ll sum=0;
            for(int j=0;j<=n;j++){
                while(r+1<=n&&r+1-c[i]<=j){
                    r++;
                    sum+=dp[i&1^1][r];
                    sum%=mod;
                }
                while(l<j-a[i]){
                    sum-=dp[i&1^1][l];
                    sum+=mod;
                    sum%=mod;
                    l++;
                }
                dp[i&1][j]=sum;
            }
        }
        return dp[t&1][n];
    };
    ll ans=sol();
    swap(a,b);
    swap(c,d);
    swap(m,n);
    ans*=sol();
    ans%=mod;
    cout << ans;
}