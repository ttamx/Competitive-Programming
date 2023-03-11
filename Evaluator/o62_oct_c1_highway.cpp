#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m,q;
bool st[N],ed[N];
vector<int> in[N],out[N];
vector<int> ans;
vector<pair<int,int>> inp;
bool closed[N];

void dfsin(int u){
	if(ed[u]||closed[u])return;
	ed[u]=1;
	for(auto v:in[u]){
		dfsin(v);
	}
}

void dfsout(int u){
	if(st[u]||closed[u])return;
	st[u]=1;
	for(auto v:out[u]){
		dfsout(v);
	}
}

int main(){
	cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> q;
	for(int i=0;i<m;++i){
		int u,v;
		cin >> u >> v;
		out[u].push_back(v);
		in[v].push_back(u);
	}
	inp.resize(q);
	for(auto &[x,y]:inp){
		cin >> x >> y;
		if(x==1)closed[y]=true;
	}
	dfsout(1);
	dfsin(n);
	reverse(inp.begin(),inp.end());
	for(auto [x,y]:inp){
		if(x==1){
			closed[y]=false;
			for(auto v:in[y]){
				if(!closed[v]&&st[v]){
					dfsout(y);
					break;
				}
			}
			for(auto v:out[y]){
				if(!closed[v]&&ed[v]){
					dfsin(y);
					break;
				}
			}
		}else{
			if(!closed[y]&&st[y]&&ed[y]){
				ans.push_back(1);
			}else{
				ans.push_back(0);
			}
		}
	}
	reverse(ans.begin(),ans.end());
	for(auto i:ans)cout << i << '\n';
}
