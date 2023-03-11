#include<bits/stdc++.h>

using namespace std;

int k,l,q,K;
int dp[10][10];
int in[10],out[10]; 

int lca(int a,int b){
	if(a>K&&b<K)return 1e6;
	if(a<K&&b>K)return 1e6;
	if(a>K&&b>K)a-=K,b-=K;
	int ret=0;
	while(a!=b){
		if(a>b)a>>=1;
		else b>>=1;
		++ret;
	}
	return ret;
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> k >> l >> q;
	K=1<<k;
	for(int i=0;i<l;++i){
		cin >> in[i] >> out[i];
		in[i+l]=out[i];
		out[i+l]=in[i];
	}
	l<<=1;
	for(int i=0;i<l;++i){
		for(int j=0;j<l;++j){
			if(i==j)dp[i][j]=1;
			else dp[i][j]=lca(in[i],out[j]);
		}
	}
	for(int i=0;i<l;++i){
		for(int j=0;j<l;++j){
			for(int m=0;m<l;++m){
				dp[i][j]=min(dp[i][j],dp[i][m]+dp[m][j]+1);
			}
		}
	}
	for(int i=0;i<q;++i){
		int a,b;
		cin >> a >> b;
		int ans=lca(a,b);
		for(int i=0;i<l;++i){
			for(int j=0;j<l;++j){
				ans=min(ans,dp[i][j]+lca(a,in[i])+lca(out[j],b));
			}
		}
		cout << ans << '\n';
	}
}