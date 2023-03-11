#include<bits/stdc++.h>

using namespace std;

const int N=2e5;

int n,m;
int pa[N];
vector<tuple<int,int,int>> edge;

int calc(int x,int y){
	return x*400+y;
}

int fp(int u){
	if(u==pa[u])return u;
	return pa[u]=fp(pa[u]);
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> m >> n;
	for(int i=0;i<m*2-1;++m){
		int x;
		if(i&1){
			for(int j=0;j<n;++j){
				cin >> x;
				edge.emplace_back(x,calc(i/2,j),calc(i/2+1,j));
			}
		}else{
			for(int j=0;i<n-1;++j){
				cin >> x;
				edge.emplace_back(x,calc(i/2,j),calc(i/2,j+1));
			}
		}
	}
	iota(pa,pa+(n+1)*(m+1)+1,0);
	sort(edge.begin(),edge.end());
	for(auto [x,u,v]:edge){
		u=fp(u);
		v=fp(v);
	}
	while(true){
		
	}
}