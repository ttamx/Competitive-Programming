#include "rescue.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;
const int M=2e5;
const int K=1<<19;
const int inf=1e9;

int n,m;
vector<p2> a;

struct fenwick{
	int n,m;
	vector<vector<int>> t;
	void init(int _n,int _m){
		n=_n+5,m=_m+5;
		t=vector<vector<int>>(n+1,vector<int>(m+1,0));
	}
	void add(int x,int y,int v){
		for(int i=x+2;i<=n;i+=i&-i)for(int j=y+2;j<=m;j+=j&-j)t[i][j]+=v;
	}
	int read(int x,int y){
		int res=0;
		for(int i=x+2;i>0;i-=i&-i)for(int j=y+2;j>0;j-=j&-j)res+=t[i][j];
		return res;
	}
	int query(int x1,int y1,int x2,int y2){
		return read(x2,y2)-read(x2,y1-1)-read(x1-1,y2)+read(x1-1,y1-1);
	}
}f;

void init_rescue(int N, int Q, vector<int> X, vector<int> Y){
	for(int i=0;i<N;i++){
		int x=X[i],y=Y[i];
		a.emplace_back(x,y);
		n=max(n,x);
		m=max(m,y);
	}
	f.init(n,m);
	for(auto [x,y]:a)f.add(x,y,1);
}

int answer_query(int A, int B, int C, int D){
	C=min(C,n),D=min(D,m);
	int cnt=f.query(A,B,C,D);
	if(cnt>0)return -cnt;
	int ans=inf;
	if(f.query(0,B,A-1,D)){
		int l=0,r=A-1;
		while(l<r){
			int mid=(l+r+1)/2;
			if(f.query(mid,B,A-1,D))l=mid;
			else r=mid-1;
		}
		ans=min(ans,A-l);
	}
	if(f.query(C+1,B,n,D)){
		int l=C+1,r=n;
		while(l<r){
			int mid=(l+r)/2;
			if(f.query(C+1,B,mid,D))r=mid;
			else l=mid+1;
		}
		ans=min(ans,l-C);
	}
	if(f.query(A,0,C,B-1)){
		int l=0,r=B-1;
		while(l<r){
			int mid=(l+r+1)/2;
			if(f.query(A,mid,C,B-1))l=mid;
			else r=mid-1;
		}
		ans=min(ans,B-l);
	}
	if(f.query(A,D+1,C,m)){
		int l=D+1,r=m;
		while(l<r){
			int mid=(l+r)/2;
			if(f.query(A,D+1,C,mid))r=mid;
			else l=mid+1;
		}
		ans=min(ans,l-D);
	}
	return ans<inf?ans:0;
}

void cancel_request(int R){
	auto [x,y]=a[R];
	f.add(x,y,-1);
}