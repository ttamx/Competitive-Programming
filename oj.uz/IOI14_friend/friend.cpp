#include "friend.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int dp[N][2];

int findSample(int n,int c[],int h[],int p[]){
	for(int i=0;i<n;i++)dp[i][0]=c[i];
	for(int i=n-1;i>=1;i--){
		int u=h[i],v=i;
		if(p[i]==0){
			dp[u][0]=dp[u][0]+dp[v][1];
			dp[u][1]=dp[u][1]+max(dp[v][0],dp[v][1]);
		}else if(p[i]==1){
			dp[u][0]=max(dp[u][0]+max(dp[v][0],dp[v][1]),dp[u][1]+dp[v][0]);
			dp[u][1]=dp[u][1]+dp[v][1];
		}else{
			dp[u][0]=max(dp[u][0]+dp[v][1],dp[u][1]+dp[v][0]);
			dp[u][1]=dp[u][1]+dp[v][1];
		}
	}
	return max(dp[0][0],dp[0][1]);
}