#include<bits/stdc++.h>

using namespace std;

const int  N=2e5+5;

int n,q,l;
int s,a,b;
int ch[N][2],dp[N][20],lv[N];
vector<int> adj[N];

int dir() {
	int res = ((s & 8) >> 3);
	s = (s * a + b) % 40507;
	return res;
}

int dfs(int u,int p){
	lv[u]=lv[p]+1;
	for(int i=0;i<adj[u].size();++i){
		ch[u][i]=dfs(adj[u][i],u);
	}
	for(int i=1;i<=17;++i)dp[u][i]=dp[dp[u][i-1]][i-1];
	if(adj[u].size()==1)return ch[u][0];
	else return u;
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> q;
	for(int i=1;i<=n;++i){
		int u,v;
		cin >> u >> v;
		++u,++v;
		if(u){
			adj[i].emplace_back(u);
			dp[i][0]=u;
		}
		if(v){
			adj[i].emplace_back(v);
			dp[i][0]=v;
		}
	}
	lv[0]=-1;
	dfs(1,0);
	lv[0]=2e9;
	while(q--){
		cin >> l >> s >> a >> b;
		int cur=1;
		bool skip=false;
		while(lv[cur]<l){
			if(adj[cur].size()==2){
				int go=dir();
				int v=ch[cur][go];
				if(lv[v]<=l)cur=v;
				else{
					cur=adj[cur][go];
					break;
				}
			}else if(adj[cur].size()==1){
				int v=ch[cur][0];
				if(lv[v]<=l)cur=v;
				else break;
			}else{
				skip=true;
				break;
			}
		}
		if(skip||lv[cur]==l){
			cout << cur-1 << '\n';
			continue;
		}
		for(int i=17;i>=0;--i)if(lv[dp[cur][i]]<=l)cur=dp[cur][i];
		cout << cur-1 << '\n';
	}
	return 0;
}