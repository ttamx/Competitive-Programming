#include<bits/stdc++.h>

using namespace std;

const int N=205;
const int INF=INT_MAX/2;

int dp[N][N][N*2];
tuple<int,int,int> pre[N][N][N*2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s,t;
    cin >> s >> t;
    int n=s.size();
    int m=t.size();
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            for(int k=0;k<=n+m;k++){
                dp[i][j][k]=INF;
            }
        }
    }
    queue<tuple<int,int,int>> q;
    dp[0][0][0]=0;
    q.emplace(0,0,0);
    while(!q.empty()){
        auto [i,j,k]=q.front();
        q.pop();
        if(k<n+m){
            int ii=i+(i<n&&s[i]=='(');
            int jj=j+(j<m&&t[j]=='(');
            if(dp[i][j][k]+1<dp[ii][jj][k+1]){
                dp[ii][jj][k+1]=dp[i][j][k]+1;
                pre[ii][jj][k+1]={i,j,k};
                q.emplace(ii,jj,k+1);
            }
        }
        if(k>0){
            int ii=i+(i<n&&s[i]==')');
            int jj=j+(j<m&&t[j]==')');
            if(dp[i][j][k]+1<dp[ii][jj][k-1]){
                dp[ii][jj][k-1]=dp[i][j][k]+1;
                pre[ii][jj][k-1]={i,j,k};
                q.emplace(ii,jj,k-1);
            }
        }
    }
    string ans="";
    for(int i=n,j=m,k=0;i>0||j>0||k>0;){
        auto [ii,jj,kk]=pre[i][j][k];
        ans.push_back("()"[kk==k+1]);
        i=ii,j=jj,k=kk;
    }
    reverse(ans.begin(),ans.end());
    cout << ans << "\n";
}