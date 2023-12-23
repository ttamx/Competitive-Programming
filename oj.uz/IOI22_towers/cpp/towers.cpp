#include "towers.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int N=1e5+5;
const int K=1<<18;
const int LG=17;
const int inf=2e9;

int n;
int h[N],spmx[LG][N],spmn[LG][N],spid[LG][N];
vector<pair<int,int>> vec;

struct persist{
	struct info{
		int mn,mx,val;
		info():mn(inf),mx(-inf),val(0){}
		info(int x):mn(x),mx(x),val(1){}
		friend info operator+(info a,info b){
			info c;
			c.mn=min(a.mn,b.mn);
			c.mx=max(a.mx,b.mx);
			c.val=a.val+b.val;
			return c;
		}
	};
	struct node;
	typedef node* pnode;
	struct node{
		info val;
		pnode l,r;
		node():val(),l(nullptr),r(nullptr){}
	};
	pnode rt[N];
	void build(int l,int r,pnode &t){
		t=new node();
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,t->l);
		build(m+1,r,t->r);
	}
	void build(int t){
		build(1,n,rt[t]);
	}
	void update(int l,int r,pnode &t,pnode k,int x){
		t=new node(*k);
		t->val=t->val+info(x);
		if(l==r)return;
		int m=(l+r)/2;
		if(x<=m)update(l,m,t->l,k->l,x);
		else update(m+1,r,t->r,k->r,x);
	}
	void update(int k,int t,int x){
		update(1,n,rt[t],rt[k],x);
	}
	info query(int l,int r,pnode t,int x,int y){
		if(y<l||r<x)return info();
		if(x<=l&&r<=y)return t->val;
		int m=(l+r)/2;
		return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
	}
	info query(int t,int x,int y){
		return query(1,n,rt[t],x,y);
	}
}pst;

struct segtree{
	struct node{
		int mn,mx,vl,vr;
		node(int x=0):mn(x),mx(x),vl(0),vr(0){}
		friend node operator+(node a,node b){
			node c;
			c.mn=min(a.mn,b.mn);
			c.mx=max(a.mx,b.mx);
			c.vl=max({a.vl,b.vl,b.mx-a.mn});
			c.vr=max({a.vr,b.vr,a.mx-b.mn});
			return c;
		}
	}t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=node(h[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(1,n,1);
	}
	node query(int l,int r,int i,int x,int y){
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		if(y<=m)return query(l,m,i*2,x,y);
		if(m<x)return query(m+1,r,i*2+1,x,y);
		return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
	}
	node query(int x,int y){
		return query(1,n,1,x,y);
	}
}s;

int rmxq(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return max(spmx[k][l],spmx[k][r-(1<<k)+1]);
}

int rmnq(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return min(spmn[k][l],spmn[k][r-(1<<k)+1]);
}

int rmidq(int l,int r){
	int k=31-__builtin_clz(r-l+1);
	return spmn[k][l]<spmn[k][r-(1<<k)+1]?spid[k][l]:spid[k][r-(1<<k)+1];
}

void init(int N,vector<int> H){
	n=N;
	for(int i=1;i<=n;i++)h[i]=H[i-1];
	h[0]=h[n+1]=inf;
	for(int i=0;i<=n+1;i++){
		spmx[0][i]=spmn[0][i]=h[i];
		spid[0][i]=i;
	}
	for(int i=1;i<LG;i++){
		for(int j=0;j+(1<<i)-1<=n+1;j++){
			spmx[i][j]=max(spmx[i-1][j],spmx[i-1][j+(1<<(i-1))]);
			spmn[i][j]=min(spmn[i-1][j],spmn[i-1][j+(1<<(i-1))]);
			spid[i][j]=spmn[i-1][j]<spmn[i-1][j+(1<<(i-1))]?spid[i-1][j]:spid[i-1][j+(1<<(i-1))];
		}
	}
	auto lb=[&](int id){
		int l=0,r=id-1;
		while(l<r){
			int m=(l+r+1)/2;
			if(rmnq(m,id)<h[id])l=m;
			else r=m-1;
		}
		return l;
	};
	auto ub=[&](int id){
		int l=id+1,r=n+1;
		while(l<r){
			int m=(l+r)/2;
			if(rmnq(id,m)<h[id])r=m;
			else l=m+1;
		}
		return l;
	};
	for(int i=1;i<=n;i++){
		int l=lb(i),r=ub(i);
		int d=min(rmxq(l,i),rmxq(i,r))-h[i];
		vec.emplace_back(d,i);
	}
	vec.emplace_back(-inf,-1);
	sort(vec.begin(),vec.end());
	pst.build(n+1);
	for(int i=n;i>=1;i--){
		pst.update(i+1,i,vec[i].second);
	}
	s.build();
}

int max_towers(int L,int R,int D){
	L++,R++;
	auto lb=[&](int id){
		int l=L-1,r=id-1;
		while(l<r){
			int m=(l+r+1)/2;
			if(rmxq(m,id)>=h[id]+D)l=m;
			else r=m-1;
		}
		return l;
	};
	auto ub=[&](int id){
		int l=id+1,r=R+1;
		while(l<r){
			int m=(l+r)/2;
			if(rmxq(id,m)>=h[id]+D)r=m;
			else l=m+1;
		}
		return l;
	};
	int ver=lower_bound(vec.begin(),vec.end(),p2(D,0))-vec.begin();
	auto res=pst.query(ver,L,R);
	int l=res.mn,r=res.mx,ans=res.val;
	if(ans==0){
		l=r=rmidq(L,R);
		ans=1;
	}
	l=lb(l),r=ub(r);
	if(L<l&&s.query(L,l).vl>=D)ans++;
	if(r<R&&s.query(r,R).vr>=D)ans++;
	return ans;
}