#include "island.h"
#include<bits/stdc++.h>

using namespace std;

void solve(int N,int L){
	vector<bool> vis(N+2);
	vis[1]=true;
	for(int i=1;i<N;i++){
		int u=query(1,i);
		if(vis[u])continue;
		vis[u]=true;
		for(int j=1;j<N;j++){
			int v=query(u,j);
			answer(u,v);
			if(vis[v])break;
			vis[v]=true;
		}
	}
}