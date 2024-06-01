#include <bits/stdc++.h>
#include "mountain.h"

using namespace std;

using ll = long long;

const int N=1e5+5;

int n;
ll a[N],c[N];

struct CartisianTree{
	int root;
	int l[N],r[N];
	void build(){
		stack<int> s;
		for(int i=0;i<n;i++){
			l[i]=r[i]=-1;
			while(!s.empty()&&a[s.top()]<a[i]){
				l[i]=s.top();
				s.pop();
			}
			if(s.empty())root=i;
			else r[s.top()]=i;
			s.emplace(i);
		}
	}
}ct;

enum Type{Compress,Rake,AddEdge,AddVertex,Vertex};

struct StaticTopTree{
	int root,node_id;
	int l[4*N],r[4*N],p[4*N];
	Type t[4*N];
	int dfs(int u){
		if(u==-1)return 0;
		int sl=dfs(ct.l[u]);
		int sr=dfs(ct.r[u]);
		if(sl<sr)swap(ct.l[u],ct.r[u]);
		return sl+sr+1;
	}
	int add(int i,int lc,int rc,Type type){
		if(i==-1)i=node_id++;
		p[i]=-1,l[i]=lc,r[i]=rc,t[i]=type;
		if(lc!=-1)p[lc]=i;
		if(rc!=-1)p[rc]=i;
		return i;
	}
	pair<int,int> merge(const vector<pair<int,int>> &a,Type type){
		if(a.size()==1)return a[0];
		int tot=0;
		for(auto [i,s]:a)tot+=s;
		vector<pair<int,int>> b,c;
		for(auto [i,s]:a){
			(tot>s?b:c).emplace_back(i,s);
			tot-=s*2;
		}
		auto [i,si]=merge(b,type);
		auto [j,sj]=merge(c,type);
		return {add(-1,i,j,type),si+sj};
	}
	pair<int,int> compress(int i){
		vector<pair<int,int>> path{add_vertex(i)};
		while(ct.l[i]!=-1)path.emplace_back(add_vertex(i=ct.l[i]));
		return merge(path,Type::Compress);
	}
	pair<int,int> rake(int i){
		return ct.r[i]==-1?make_pair(-1,0):add_edge(ct.r[i]);
	}
	pair<int,int> add_edge(int i){
		auto [j,s]=compress(i);
		return {add(-1,j,-1,Type::AddEdge),s};
	}
	pair<int,int> add_vertex(int i){
		auto [j,s]=rake(i);
		return {add(i,j,-1,j==-1?Type::Vertex:Type::AddVertex),s+1};
	}
	void build(){
		node_id=n;
		dfs(ct.root);
		root=compress(ct.root).first;
	}
}stt;

struct Point{
	ll ans;
	array<ll,2> cnt;
	Point():ans(0){
		cnt[0]=cnt[1]=0;
	}
}point[4*N];

struct Path{
	ll ans;
	array<ll,2> sum,cnt;
	Path():ans(0){
		sum[0]=sum[1]=cnt[0]=cnt[1]=0;
	}
}path[4*N];

Path compress(Path p,Path c){
	Path res;
	res.ans=p.ans+c.ans;
	for(int i=0;i<2;i++){
		res.sum[i]=p.sum[i]+c.sum[i];
		res.cnt[i]=p.cnt[i]+c.cnt[i];
		res.ans+=p.sum[i]*c.cnt[i^1];
	}
	return res;
}
Point add_edge(Path d){
	Point res;
	res.ans=d.ans,res.cnt=d.cnt;
	return res;
}
Path add_vertex(Point d,int i){
	Path res;
	res.ans=d.ans,res.cnt=d.cnt;
	if(c[i])res.ans+=d.cnt[(c[i]-1)^1]*a[i],res.cnt[c[i]-1]++;
	for(int j=0;j<2;j++)res.sum[j]=res.cnt[j]*a[i];
	return res;
}
Path vertex(int i){
	Path res;
	if(c[i])res.sum[c[i]-1]=a[i],res.cnt[c[i]-1]=1;
	return res;
}

void update(int i){
	if(stt.t[i]==Type::Compress)path[i]=compress(path[stt.l[i]],path[stt.r[i]]);
	else if(stt.t[i]==Type::AddEdge)point[i]=add_edge(path[stt.l[i]]);
	else if(stt.t[i]==Type::AddVertex)path[i]=add_vertex(point[stt.l[i]],i);
	else path[i]=vertex(i);
}

void dfs(int u){
	if(u==-1)return;
	dfs(stt.l[u]);
	dfs(stt.r[u]);
	update(u);
}

void initialize(int _n,vector<int> A,vector<int> C){
	n=_n;
	for(int i=0;i<n;i++)a[i]=A[i],c[i]=C[i];
	ct.build();
	stt.build();
	dfs(stt.root);
}

ll race_cost(int S,int X){
	c[X]=S;
	for(;X!=-1;X=stt.p[X])update(X);
	return path[stt.root].ans;
}
