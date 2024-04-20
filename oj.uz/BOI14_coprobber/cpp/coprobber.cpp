#include "coprobber.h"
#include<bits/stdc++.h>

using namespace std;

int n,st;
vector<int> adj[MAX_N];
bool vis[MAX_N][MAX_N][2];
pair<int,int> dp[MAX_N][MAX_N][2];
int cnt[MAX_N][MAX_N][2];
queue<tuple<int,int,int>> q;

int start(int N,bool A[MAX_N][MAX_N]){
    n=N;
    for(int u=0;u<n;u++)for(int v=0;v<n;v++)if(A[u][v])adj[u].emplace_back(v);
    for(int i=0;i<n;i++){
        dp[i][i][0]={0,-1};
        dp[i][i][1]={1,-1};
        vis[i][i][0]=true;
        vis[i][i][1]=true;
        q.emplace(i,i,0);
        q.emplace(i,i,1);
    }
    while(!q.empty()){
        auto [x,y,t]=q.front();
        q.pop();
        if(t){
            for(auto u:adj[y])if(!vis[x][u][0]){
                if(dp[x][y][t].first==0){
                    dp[x][u][0]={1,y};
                    vis[x][u][0]=true;
                    q.emplace(x,u,0);
                }else if(++cnt[x][u][0]==adj[u].size()){
                    vis[x][u][0]=true;
                    q.emplace(x,u,0);
                }
            }
        }else{
            if(!vis[x][y][1]){
                if(dp[x][y][t].first==0){
                    dp[x][y][1]={1,x};
                    vis[x][y][1]=true;
                    q.emplace(x,y,1);
                }else if(++cnt[x][y][1]==adj[x].size()+1){
                    vis[x][y][1]=true;
                    q.emplace(x,y,1);
                }
            }
            for(auto u:adj[x])if(!vis[u][y][1]){
                if(dp[x][y][t].first==0){
                    dp[u][y][1]={1,x};
                    vis[u][y][1]=true;
                    q.emplace(u,y,1);
                }else if(++cnt[u][y][1]==adj[u].size()+1){
                    vis[u][y][1]=true;
                    q.emplace(u,y,1);
                }
            }
        }
    }
    for(int u=0;u<n;u++){
        int res=1;
        for(int v=0;v<n;v++){
            res=min(res,dp[u][v][1].first);
        }
        if(res)return st=u;
    }
    return -1;
}

int nextMove(int R){
    return st=dp[st][R][1].second;
}
