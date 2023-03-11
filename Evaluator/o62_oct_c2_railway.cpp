#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;

int n,m;
int lv[N],p[N];
int pa[N][5],mx[N][5];
vector<p2> adj[N];
vector<int> req;
set<int> nonmst;
vector<int> ans;

int fp(int u){
	if(u==p[u])return u;
	return p[u]=fp(p[u]);
}

void dfs(int u,int p,int c){
	pa[u][0]=p;
	lv[u]=lv[p]+1;
	mx[u][0]=c;
	for(int i=1;i<4;++i){
		pa[u][i]=pa[pa[u][i-1]][i-1];
		mx[u][i]=max(mx[u][i-1],mx[pa[u][i-1]][i-1]);
	}
	for(auto [w,v]:adj[u]){
		if(v==p)continue;
		dfs(v,u,w);
	}
}

int lca(int x,int y){
	int ret=0;
	if(lv[x]<lv[y])swap(x,y);
	for(int i=4;i>=0;--i){
		if(lv[pa[x][i]]>=lv[y]){
			ret=max(ret,mx[x][i]);
			x=pa[x][i];
		}
	}
	if(x==y)return ret;
	for(int i=4;i>=0;--i){
		if(pa[x][i]!=pa[y][i]){
			ret=max(ret,mx[x][i]);
			ret=max(ret,mx[y][i]);
			x=pa[x][i];
			y=pa[y][i];
		}
	}
	return max({ret,mx[x][0],mx[y][0]});
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for(int i=0;i<n-1;i++){
		int u,v,w;
		cin >> u >> v >> w;
		adj[u].emplace_back(w,v);
		adj[v].emplace_back(w,u);
	}
	dfs(1,0,0);
	for(int i=n-1;i<m;++i){
		int u,v,w;
		cin >> u >> v >> w;
		nonmst.insert(w);
		req.emplace_back(lca(u,v)+1);
	}
	for(auto w:req){
		auto it=nonmst.lower_bound(w);
		if(it==nonmst.end()){
			cout << 0;
			return 0;
		}
		ans.emplace_back(*it);
		nonmst.erase(it);
	}
	cout << 1 << '\n';
	for(auto i:ans)cout << i << '\n';
}