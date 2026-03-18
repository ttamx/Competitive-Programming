#include<bits/stdc++.h>

using namespace std;

const int N=10005;
const int INF=INT_MAX/2;

int n,m;
int dp[N][N];
int pos[2*N],nxt[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    n=s.size(),m=t.size();
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            dp[i][j]=INF;
        }
    }
    int last=n+1;
    int bal=N;
    pos[N]=n;
    for(int i=n-1;i>=0;i--){
        nxt[i]=n+1;
        if(s[i]=='.'){
            bal++;
        }else{
            bal--;
            if(pos[bal]){
                nxt[i]=pos[bal];
            }
        }
        pos[bal]=i;
    }
    dp[0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=m;j++){
            dp[i+1][j]=min(dp[i+1][j],dp[i][j]+1);
            if(j<m&&s[i]==t[j]){
                dp[i+1][j+1]=min(dp[i+1][j+1],dp[i][j]);
            }
            if(s[i]=='.'&&j>0){
                dp[i+1][j-1]=min(dp[i+1][j-1],dp[i][j]);
            }
            if(nxt[i]<=n){
                dp[nxt[i]][j]=min(dp[nxt[i]][j],dp[i][j]);
            }
        }
    }
    cout << dp[n][m] << "\n";
}