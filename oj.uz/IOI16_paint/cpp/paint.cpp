#include "paint.h"
#include <bits/stdc++.h>

using namespace std;

typedef tuple<int,int,int> t3;

const int N=2e5+5;
const int K=105;

bool dp[N][K][2],vis[N][K][2];
int white[N];
int iswhite[N],isblack[N];

bool valid(int l,int r){
    return white[l]>r;
}

string solve_puzzle(string s, vector<int> c) {
    int n=s.size();
    for(int i=0;i<n;i++)if(s[i]=='_')white[i]=i;
    white[n]=n;
    for(int i=n-1;i>=0;i--)if(white[i]==0)white[i]=white[i+1];
    int m=c.size();
    dp[0][0][0]=true;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=m;j++){
            if(s[i-1]=='_'||s[i-1]=='.'){
                dp[i][j][0]|=dp[i-1][j][0];
                if(j>0)dp[i][j][0]|=dp[i-1][j-1][1];
            }
            if(s[i-1]=='X'||s[i-1]=='.'){
                if(j<m&&i>=c[j]&&valid(i-c[j],i-1)){
                    dp[i][j][1]|=dp[i-c[j]][j][0];
                }
            }
        }
    }
    queue<t3> q;
    if(dp[n][m][0]){
        vis[n][m][0]=true;
        q.emplace(n,m,0);
    }
    if(dp[n][m-1][1]){
        vis[n][m-1][1]=true;
        q.emplace(n,m-1,1);
    }
    while(!q.empty()){
        auto [i,j,k]=q.front();
        q.pop();
        if(i==0)continue;
        if(s[i-1]=='_'||s[i-1]=='.'){
            if(k==0&&dp[i-1][j][0]){
                iswhite[i-1]=1;
                if(!vis[i-1][j][0]){
                    vis[i-1][j][0]=true;
                    q.emplace(i-1,j,0);
                }
            }
            if(k==0&&j>0&&dp[i-1][j-1][1]){
                iswhite[i-1]=1;
                if(!vis[i-1][j-1][1]){
                    vis[i-1][j-1][1]=true;
                    q.emplace(i-1,j-1,1);
                }
            }
        }
        if(s[i-1]=='X'||s[i-1]=='.'){
            if(k==1&&j<m&&i>=c[j]&&valid(i-c[j],i-1)&&dp[i-c[j]][j][0]){
                isblack[i-c[j]]++,isblack[i]--;
                if(!vis[i-c[j]][j][0]){
                    vis[i-c[j]][j][0]=true;
                    q.emplace(i-c[j],j,0);
                }
            }
        }
    }
    for(int i=1;i<n;i++)isblack[i]+=isblack[i-1];
    string ans(n,'?');
    for(int i=0;i<n;i++){
        if(isblack[i]&&!iswhite[i])ans[i]='X';
        if(!isblack[i]&&iswhite[i])ans[i]='_';
    }
    return ans;
}
