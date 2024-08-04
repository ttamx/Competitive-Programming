#include "soccer.h"
#include <bits/stdc++.h>

using namespace std;

const int N=2005;

int n;
int a[N][N];
int top[N][N],bot[N][N],pre[N][N][2],dp[N][N];
vector<pair<int,int>> rect[N];
int ans;

int biggest_stadium(int _n,vector<vector<int>> _a){
    n=_n;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)a[i][j]=_a[i-1][j-1]^1;
    for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)top[i][j]=a[i][j]?a[i-1][j]?top[i-1][j]:i:top[i-1][j];
    for(int i=1;i<=n;i++)bot[n+1][i]=n+1;
    for(int i=n;i>=1;i--)for(int j=1;j<=n;j++)bot[i][j]=a[i][j]?a[i+1][j]?bot[i+1][j]:i:bot[i+1][j];
    for(int i=1;i<=n;i++){
        int t=0,b=n+1;
        for(int j=1;j<=n;j++){
            for(int x=0;x<2;x++)pre[i][j][x]=a[i][j]==x?j:pre[i][j-1][x];
            if(a[i][j]){
                if(a[i][j-1]){
                    top[i][j]=max(top[i][j],top[i][j-1]);
                    bot[i][j]=min(bot[i][j],bot[i][j-1]);
                }
                rect[j-pre[i][j][0]].emplace_back(i,j);
            }
        }
    }
    for(int w=n;w>=1;w--)for(auto [i,j]:rect[w]){
        int l=pre[i][j][0]+1,r=j,t=top[i][j],b=bot[i][j];
        if(a[i][j+1]&&top[i][j+1]<=t&&bot[i][j+1]>=b)continue;
        int lw=l>1?bot[i][l-1]+1:i+1;
        if(lw<=b){
            dp[lw][j]=max(dp[lw][j],dp[i][j]);
            continue;
        }
        int h=b-t+1;
        int res=w*h+dp[i][j];
        ans=max(ans,res);
        for(int x:{t-1,b+1}){
            for(int nr=pre[x][r][1],nl;nr>=l;nr=pre[x][nl][1]){
                nl=max(l-1,pre[x][nr][0]);
                int p=nl>=l?x:i;
                dp[p][nr]=max(dp[p][nr],res-(nr-nl)*h);
            }
        }
    }
    return ans;
}