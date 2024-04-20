#include "island.h"
#include<bits/stdc++.h>

using namespace std;

void solve(int N,int L){
	vector<bool> vis(N+2);
	int u=query(1,N-1);
	vis[u]=true;
	for(int i=1;i<N;i++){
		int v=query(u,1);
		if(vis[v])v=query(u,2);
		answer(u,v);
		u=v;
		vis[u]=true;
	}
}