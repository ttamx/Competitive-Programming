#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=15;
const int M=105;
const int mod=1e9+7;

int n,m,k;
int a[M];
ll cnt[N][M];
ll dp[M][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> n >> s >> k;
    m=s.size();
    for(int i=1;i<=m;i++)a[i]=s[m-i]-'0';
    cnt[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int d=0;d<=9;d++){
            if(d==k)continue;
            for(int j=d;j<=90;j++){
                cnt[i][j]+=cnt[i-1][j-d];
                cnt[i][j]%=mod;
            }
        }
    }
    dp[0][0]=1;
    for(int i=1;i<=m;i++){
        for(int j=0;j<=9;j++){
            for(int v=0;v<=99;v++){
                if(cnt[n][v]==0||(j+v)%10!=a[i])continue;
                dp[i][(j+v)/10]+=dp[i-1][j]*cnt[n][v];
                dp[i][(j+v)/10]%=mod;
            }
        }
    }
    cout << dp[m][0];
}