#include "findhome.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=305;

int n;
int dist[N][N];
bool used[N];

int find_home(int N, int M, vector<pair<int,int>> R){
	n=N;
	for(int i=0;i<n;i++)for(int j=0;j<n;j++)dist[i][j]=n;
	for(auto [u,v]:R)dist[u][v]=dist[v][u]=1;
	for(int i=0;i<n;i++)dist[i][i]=0;
	for(int k=0;k<n;k++)for(int i=0;i<n;i++)for(int j=0;j<n;j++)dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
	int cur=n;
	while(cur>1){
		p2 mn(n,-1);
		for(int u=0;u<n;u++)if(!used[u]){
			int mx=0;
			for(int v=0;v<n;v++)if(dist[u][v]==1){
				int cnt=0;
				for(int i=0;i<n;i++)cnt+=!used[i]&&dist[u][i]==1+dist[v][i];
				mx=max(mx,cnt);
			}
			mn=min(mn,p2(mx,u));
		}
		int u=mn.second;
		int v=check(u);
		if(u==v)return u;
		for(int i=0;i<n;i++)if(!used[i]&&dist[u][i]!=1+dist[v][i])used[i]=true,cur--;
	}
	for(int i=0;i<n;i++)if(!used[i])return i;
	return -1;
}
