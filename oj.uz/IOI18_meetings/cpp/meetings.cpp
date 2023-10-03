#include "meetings.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

const int N=750005;
const int K=1<<21;

int n,q;
ll h[N];
int lg[N];
int ql[N],qr[N];
vector<int> qry[N];
vector<ll> ans;
p2 sp[20][N];

struct lichaotree{
	struct line{
		ll m,c;
		line(ll m=0,ll c=1e18):m(m),c(c){}
		ll get(ll x){
			return m*x+c;
		}
	}t[K];
	ll lz[K];
	void pushlz(int l,int r,int i){
		if(!lz[i])return;
		t[i].c+=lz[i];
		if(l<r){
			lz[i*2]+=lz[i];
			lz[i*2+1]+=lz[i];
		}
		lz[i]=0;
	}
	void update(int l,int r,int i,int x,int y,line v){
		pushlz(l,r,i);
		if(y<l||r<x)return;
		int m=(l+r)/2;
		if(x<=l&&r<=y){
			if(v.get(m)<t[i].get(m))swap(t[i],v);
			if(v.get(l)<t[i].get(l))update(l,m,i*2,x,y,v);
			if(v.get(r)<t[i].get(r))update(m+1,r,i*2+1,x,y,v);
		}else{
			update(l,m,i*2,x,y,v);
			update(m+1,r,i*2+1,x,y,v);
		}
	}
	void update(int x,int y,ll m,ll c){
		update(1,n,1,x,y,line(m,c));
	}
	void addval(int l,int r,int i,int x,int y,ll v){
		pushlz(l,r,i);
		if(y<l||r<x)return;
		if(x<=l&&r<=y)return lz[i]+=v,pushlz(l,r,i),void();
		int m=(l+r)/2;
		addval(l,m,i*2,x,y,v);
		addval(m+1,r,i*2+1,x,y,v);
	}
	void addval(int x,int y,ll v){
		addval(1,n,1,x,y,v);
	}
	ll query(int l,int r,int i,int x){
		pushlz(l,r,i);
		ll res=t[i].get(x);
		if(l==r)return res;
		int m=(l+r)/2;
		if(x<=m)return min(res,query(l,m,i*2,x));
		else return min(res,query(m+1,r,i*2+1,x));
	}
	ll query(int x){
		return query(1,n,1,x);
	}
}lctl,lctr;

p2 rmq(int l,int r){
	int k=lg[r-l+1];
	return max(sp[k][l],sp[k][r-(1<<k)+1]);
}

void solve(int l,int r){
	if(l>r)return;
	int m=rmq(l,r).second;
	solve(l,m-1);
	solve(m+1,r);
	lctl.update(m,m,0,0);
	lctr.update(m,m,0,0);
	for(auto i:qry[m]){
		ans[i]=min(lctl.query(ql[i])+h[m]*(qr[i]-m+1),lctr.query(qr[i])+h[m]*(m-ql[i]+1));
	}
	lctl.addval(l,m,h[m]*(r-m+1));
	lctl.update(l,m,-h[m],h[m]*(m+1)+lctl.query(m+1));
	lctr.addval(m,r,h[m]*(m-l+1));
	lctr.update(m,r,h[m],h[m]*(-m+1)+lctr.query(m-1));
}

vector<ll> minimum_costs(vector<int> H, vector<int> L, vector<int> R) {
	n=H.size();
	q=L.size();
	ans.resize(q);
	for(int i=1;i<=n;i++){
		h[i]=H[i-1];
		sp[0][i]=p2(h[i],i);
	}
	for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
	for(int i=1;i<=lg[n];i++){
		for(int j=1;j+(1<<i)-1<=n;j++){
			sp[i][j]=max(sp[i-1][j],sp[i-1][j+(1<<(i-1))]);
		}
	}
	for(int i=0;i<q;i++){
		ql[i]=L[i]+1;
		qr[i]=R[i]+1;
		qry[rmq(ql[i],qr[i]).second].emplace_back(i);
	}
	solve(1,n);
	return ans;
}