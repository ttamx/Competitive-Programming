#include "manager.h"
#include<bits/stdc++.h>

using namespace std;

const int N=50005;
const int K=230;

int n,q;
int a[N];
int dp[K][N][20];
map<int,int> pre;

struct persist{
	struct node{
		int val;
		node *l,*r;
		node():val(0),l(nullptr),r(nullptr){}
		node(int val):val(val),l(nullptr),r(nullptr){}
	};
	typedef node* pnode;
	pnode rt[N];
	void build(int l,int r,pnode &t){
		t=new node();
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,t->l);
		build(m+1,r,t->r);
	}
	void build(int cur){
		build(0,n,rt[cur]);
	}
	void update(int l,int r,pnode &t,pnode k,int x,int v){
		t=new node(*k);
		t->val+=v;
		if(l==r)return;
		int m=(l+r)/2;
		if(x<=m)update(l,m,t->l,k->l,x,v);
		else update(m+1,r,t->r,k->r,x,v);
	}
	void update(int pre,int cur,int x,int v){
		update(0,n,rt[cur],rt[pre],x,v);
	}
	int query(int l,int r,pnode t,int v){
		if(l==r)return l;
		int m=(l+r)/2;
		if(t->l->val<=v)return query(m+1,r,t->r,v-t->l->val);
		else return query(l,m,t->l,v);
	}
	int query(int cur,int v){
		return query(0,n,rt[cur],v);
	}
}s;

void initialize(int N, int Q, vector<int> A){
	n=N,q=Q;
	for(int i=0;i<n;i++)a[i]=A[i];
	s.build(n);
	for(int i=n-1;i>=0;i--){
		s.update(i+1,i,i,1);
		if(pre[a[i]])s.update(i,i,pre[a[i]],-1);
		pre[a[i]]=i;
	}
	for(int i=1;i<K;i++){
		for(int j=0;j<=n;j++){
			dp[i][j][0]=s.query(j,i);
		}
	}
	for(int k=1;k<=16;k++){
		for(int i=1;i<K;i++){
			for(int j=0;j<=n;j++){
				dp[i][j][k]=dp[i][dp[i][j][k-1]][k-1];
			}
		}
	}
}

int min_managers(int l, int r, int x){
	int ans=0;
	if(x<K){
		for(int i=16;i>=0;i--){
			if(dp[x][l][i]<=r){
				ans+=1<<i;
				l=dp[x][l][i];
			}
		}
		ans++;
	}else{
		while(l<=r){
			ans++;
			l=s.query(l,x);
		}
	}
	return ans;
}
