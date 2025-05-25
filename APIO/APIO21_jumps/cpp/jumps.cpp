#include "jumps.h"
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int LG=18;

int n;
int a[N];
int pre[N],nxt[N],best[N];

struct Doubling{
	int dp[N][LG];
	void build(int* a){
		for(int i=0;i<=n+1;i++)dp[i][0]=a[i];
		for(int j=1;j<LG;j++)for(int i=0;i<=n+1;i++)dp[i][j]=dp[dp[i][j-1]][j-1];
	}
	template<class F>
	pair<int,int> query(int x,F f){
		int res=0;
		for(int i=LG-1;i>=0;i--)if(f(dp[x][i])){
			x=dp[x][i];
			res|=1<<i;
		}
		return {x,res};
	}
}l,r,h;

void init(int _n,vector<int> _a){
	n=_n;
	for(int i=1;i<=n;i++)a[i]=_a[i-1];
	a[0]=a[n+1]=n+1;
	stack<int> s;
	for(int i=1;i<=n;i++){
		while(!s.empty()&&a[s.top()]<a[i])s.pop();
		pre[i]=s.empty()?0:s.top();
		s.emplace(i);
	}
	pre[0]=pre[n+1]=0;
	while(!s.empty())s.pop();
	for(int i=n;i>=1;i--){
		while(!s.empty()&&a[s.top()]<a[i])s.pop();
		nxt[i]=s.empty()?n+1:s.top();
		s.emplace(i);
	}
	nxt[0]=nxt[n+1]=n+1;
	for(int i=1;i<=n;i++)best[i]=a[pre[i]]>a[nxt[i]]?pre[i]:nxt[i];
	best[0]=best[n+1]=0;
	l.build(pre);
	r.build(nxt);
	h.build(best);
}

int minimum_jumps(int a,int b,int c,int d){
	a++,b++,c++,d++;
	int u=b;
	u=l.query(u,[&](int x){return x>=a&&nxt[x]<=d;}).first;
	if(c<=nxt[u]&&nxt[u]<=d)return 1;
	int ans,cost;
	tie(u,ans)=h.query(u,[&](int x){return nxt[x]<c;});
	if(nxt[best[u]]<=d)return ans+2;
	tie(u,cost)=r.query(u,[&](int x){return nxt[x]<c;});
	u=nxt[nxt[u]];
	return c<=u&&u<=d?ans+cost+2:-1;
}