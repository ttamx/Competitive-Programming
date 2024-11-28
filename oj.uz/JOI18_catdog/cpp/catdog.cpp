#include "catdog.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
vector<int> adj[N];
int t[N];

enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};

struct StaticTopTree{
	using P = pair<int,int>;
	int root,node_id;
	int hv[N],p[N];
	int lch[4*N],rch[4*N],par[4*N];
	Type type[4*N];
	int dfs(int u){
		int s=1,mx=0;
		for(auto v:adj[u]){
			if(v==p[u])continue;
			p[v]=u;
			int t=dfs(v);
			if(t>mx)mx=t,hv[u]=v;
			s+=t;
		}
		return s;
	}
	int add(int i,int l,int r,Type t){
		if(!i)i=++node_id;
		lch[i]=l,rch[i]=r,type[i]=t;
		if(l)par[l]=i;
		if(r)par[r]=i;
		return i;
	}
	P merge(const vector<P> &a,Type t){
		if(a.size()==1)return a[0];
		int tot=0;
		vector<P> b,c;
		for(auto [i,s]:a)tot+=s;
		for(auto [i,s]:a){
			(tot>s?b:c).emplace_back(i,s);
			tot-=s*2;
		}
		auto [i,si]=merge(b,t);
		auto [j,sj]=merge(c,t);
		return {add(0,i,j,t),si+sj};
	}
	P compress(int i){
		vector<P> a{add_vertex(i)};
		while(hv[i])a.emplace_back(add_vertex(i=hv[i]));
		return merge(a,Compress);
	}
	P rake(int i){
		vector<P> a;
		for(auto j:adj[i])if(j!=p[i]&&j!=hv[i])a.emplace_back(add_edge(j));
		return a.empty()?P(0,0):merge(a,Rake);
	}
	P add_edge(int i){
		auto [j,s]=compress(i);
		return {add(0,j,0,AddEdge),s};
	}
	P add_vertex(int i){
		auto [j,s]=rake(i);
		return {add(i,j,0,j?AddVertex:Vertex),s+1};
	}
	void build(){
		node_id=n;
		dfs(1);
		root=compress(1).first;
	}
}stt;

using Path = array<array<int,2>,2>;
using Point = array<int,2>;

Path path[4*N];
Point point[4*N];

Path compress(Path l,Path r){
	Path res;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			res[i][j]=n;
			for(int x=0;x<2;x++){
				for(int y=0;y<2;y++){
					res[i][j]=min(res[i][j],l[i][x]+r[y][j]+(x!=y));
				}
			}
		}
	}
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			for(int x=0;x<2;x++){
				for(int y=0;y<2;y++){
					res[i][j]=min(res[i][j],res[x][y]+(i!=x)+(j!=y));
				}
			}
		}
	}
	return res;
}

Point rake(Point l,Point r){
	return {l[0]+r[0],l[1]+r[1]};
}

Point add_edge(Path p){
	return {min(p[0][0],p[0][1]),min(p[1][0],p[1][1])};
}

Path add_vertex(Point p,int u){
	Path res;
	for(auto &v:res)v.fill(n);
	for(int v=0;v<2;v++){
		if(t[u]==-1||t[u]==v){
			for(int i=0;i<2;i++){
				for(int j=0;j<2;j++){
					res[i][j]=min(res[i][j],p[v]+(i!=v)+(j!=v));
				}
			}
		}
	}
	return res;
}

Path vertex(int u){
	Path res;
	for(auto &v:res)v.fill(n);
	for(int v=0;v<2;v++){
		if(t[u]==-1||t[u]==v){
			for(int i=0;i<2;i++){
				for(int j=0;j<2;j++){
					res[i][j]=min(res[i][j],(i!=v)+(j!=v));
				}
			}
		}
	}
	return res;
}

void update(int u){
	if(stt.type[u]==Compress){
		path[u]=compress(path[stt.lch[u]],path[stt.rch[u]]);
	}else if(stt.type[u]==Rake){
		point[u]=rake(point[stt.lch[u]],point[stt.rch[u]]);
	}else if(stt.type[u]==AddEdge){
		point[u]=add_edge(path[stt.lch[u]]);
	}else if(stt.type[u]==AddVertex){
		path[u]=add_vertex(point[stt.lch[u]],u);
	}else if(stt.type[u]==Vertex){
		path[u]=vertex(u);
	}
}

void dfs(int u){
	if(!u)return;
	dfs(stt.lch[u]);
	dfs(stt.rch[u]);
	update(u);
}

int solve(int u,int nt){
	t[u]=nt;
	for(;u;u=stt.par[u]){
		update(u);
	}
	int ans=n;
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			ans=min(ans,path[stt.root][i][j]);
		}
	}
	return ans;
}

void initialize(int _n,vector<int> _u,vector<int> _v){
	n=_n;
	for(int i=0;i<n-1;i++){
		int u=_u[i],v=_v[i];
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	fill(t+1,t+n+1,-1);
	stt.build();
	dfs(stt.root);
}

int cat(int v){
	return solve(v,0);
}

int dog(int v){
	return solve(v,1);
}

int neighbor(int v){
	return solve(v,-1);
}
