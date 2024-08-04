#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int T=20005;
const int N=55;
const int S=55;
const int K=1<<16;
const ll INF=LLONG_MAX/2;

int m,n,s;
ll p[T],qs[T];
string a[N];
ll dp[S][T];
int ptr[N],pre[T][N];

ll mn[S];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s;
    for(int i=1;i<=m;i++)cin >> p[i];
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=m;i++)qs[i]=qs[i-1]+p[i];
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            pre[i][j]=a[j][i-1]=='1'?pre[i-1][j]:i;
        }
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cerr << pre[j][i] << " \n"[j==m];
    cerr << "----\n";
    for(int i=1;i<=m;i++)sort(pre[i]+1,pre[i]+n+1);
    for(int i=0;i<=s;i++)for(int j=0;j<=m;j++)dp[i][j]=INF;
    dp[0][0]=0;
    for(int i=1;i<=s;i++){
        for(int j=1;j<=n;j++){
            mn[j]=INF;
            ptr[j]=0;
        }
        for(int j=1;j<=m;j++){
            for(int k=1;k<=n;k++){
                if(pre[j][k]==j){
                    mn[k]=INF;
                    ptr[k]=j;
                }else{
                    for(int &x=ptr[k];x<i;x++){
                        mn[k]=min(mn[k],dp[i-1][x]-qs[x]*k);
                    }
                }
                dp[i][j]=min(dp[i][j],mn[k]+qs[j]*k);
            }
            cerr << dp[i][j] << " \n"[j==m];
        }
    }
    for(int i=1;i<=s;i++)cout << dp[i][m] << "\n";
}