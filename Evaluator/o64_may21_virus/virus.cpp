#include "virus.h"
#include <bits/stdc++.h>

using namespace std;

const int N=305;
const int MOD=1e9+7;

int n;
long long dp[2][N][N][3][3];
long long ans[N];

void upd(long long &t,long long v){
	t=(t+v)%MOD;
}

void initialize(int _n,int st,int ed){
	n=_n;
	dp[1][1][0][(st==1||ed==1)?1:0][(st==1||ed==1)?1:0]=1;
	for(int i=2;i<=n;i++){
		int cur=i&1;
		int pre=cur^1;
		for(int j=1;j<=i;j++){
			for(int k=0;k<i;k++){
				for(int e=0;e<3;e++){
					for(int t=0;t<3;t++){
						dp[cur][j][k][e][t]=0;
					}
				}
			}
		}
		if(st==i||ed==i){
			for(int j=1;j<i;j++){
				for(int k=0;k<i;k++){
					for(int e=0;e<2;e++){
						for(int t=0;t<2;t++){
							long long val=dp[pre][j][k][e][t];
							upd(dp[cur][j+1][k][e+1][t+1],val);
							upd(dp[cur][j][k][e+1][t],val);
						}
					}
				}
			}
		}else{
			for(int j=1;j<i;j++){
				for(int k=0;k<i;k++){
					for(int e=0;e<3;e++){
						for(int t=0;t<3;t++){
							long long val=dp[pre][j][k][e][t];
							upd(dp[cur][j+1][k][e][t],val*(j+1-e));
							upd(dp[cur][j][k][e][t],val*(2*j-e));
							upd(dp[cur][j-1][k+1][e][t],val*(j-1));
						}
					}
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<3;j++){
			int t=i*2+1-j;
			if(t<0)continue;
			upd(ans[t],dp[n&1][1][i][2][j]);
		}
	}
}

int ask(int x){
  	return ans[x];
}