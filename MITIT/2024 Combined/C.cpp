#include<iostream>
#include<stack>
#include<map>
#include<vector>
#include<string>
#include<cassert>
#include<unordered_map>
#include <queue>
#include <cstdint>
#include<cstring>
#include<limits.h>
#include<cmath>
#include<set>
#include<algorithm>
#include <iomanip>
#include<numeric>
#include<bitset>
using namespace std;
#define ll long long
#define f first
#define s second
#define pii pair<int,int>
#define ppii pair<int,pii>
#define vi vector<int>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define F(n) for(int i=0;i<n;i++)
#define lb lower_bound
#define ub upper_bound
#define fastio ios::sync_with_stdio(false);cin.tie(NULL);
#pragma GCC optimize ("03,unroll-lopps")
#define int long long
using namespace std;
const int mod=1e9+7,mxn=2e5+5,inf=1e18,minf=-1e18,lg=30;
//#undef int
int n,k,m;
void setIO(string name){		
	ios_base::sync_with_stdio(0); cin.tie(0);		
	freopen((name+".in").c_str(),"r",stdin);		
	freopen((name+".out").c_str(),"w",stdout);	
}
char grid[1002][1002];
void solve(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin>>grid[i][j];
	int ans=1;
	for(int i=1;i<=n;i++)for(int j=1;j<=m;j++){
		if(grid[i][j]!='o')continue;
		int cv=0,ch=0;
		if(i-1>0&&grid[i-1][j]=='.')cv++;
		if(i+1<=n&&grid[i+1][j]=='.')cv++;
		if(j-1>0&&grid[i][j-1]=='.')ch++;
		if(j+1<=m&&grid[i][j+1]=='.')ch++;
		if(cv*ch==0)return void(cout<<0<<'\n');
		if(cv==1){
			grid[i][j]='o';
			if(i-1>0&&grid[i-1][j]=='.')grid[i-1][j]='#';
			if(i+1<=n&&grid[i+1][j]=='.')grid[i+1][j]='#';
		}
        if(ch==1){
			grid[i][j]='#';
			if(j-1>0&&grid[i][j-1]=='.')grid[i][j-1]='#';
			if(j+1<=m&&grid[i][j+1]=='.')grid[i][j+1]='#';
        }
	}
	for(int i=1;i<=n;i++){
		vector<int>dp(m+2,0);
		//number of ways to arange within prefix i
		dp[0]=1;
		for(int j=1;j<=m;j++){
			dp[j]=(dp[j]+dp[j-1])%mod;
			if(grid[i][j]=='o'){
				if(grid[i][j-1]=='.')dp[j]=dp[j-2];
				else dp[j]=0;
				if(grid[i][j+1]=='.')dp[j+1]=(dp[j+1]+dp[j-1])%mod;
			}
		}
		ans=(ans*dp[m])%mod;
	}
	cout<<ans<<'\n';
}
int32_t main(){
    fastio
	int t;cin>>t;
	while(t--)solve();
}