#include <bits/stdc++.h>

using namespace std;

mt19937_64 rng(134263);

const int N=60005;
const int X=1e6+5;
const int S=200;
const int B=605;

int n,m;
long long hsh[X];
bool not_prime[X];
map<long long,vector<int>> posa,posb;
vector<long long> vals;
vector<int> pts[N];
int dpa[B][N],dpb[B][N];
int idx;

struct Persist{
	struct Node;
	using Ptr = Node*;
	struct Node{
		int val;
		Ptr l,r;
		Node():val(0),l(),r(){}
	};
	Ptr root[N];
	void build(int l,int r,Ptr &t){
		t=new Node();
		if(l==r)return;
		int m=(l+r)/2;
		build(l,m,t->l);
		build(m+1,r,t->r);
	}
	void build(int ver){
		build(1,m,root[ver]);
	}
	void update(int l,int r,Ptr &t,Ptr o,int x){
		t=new Node(*o);
		t->val++;
		if(l==r)return;
		int m=(l+r)/2;
		if(x<=m)update(l,m,t->l,o->l,x);
		else update(m+1,r,t->r,o->r,x);
	}
	void update(int pre,int cur,int x){
		update(1,m,root[cur],root[pre],x);
	}
	int query(int l,int r,Ptr tl,Ptr tr,int x,int y){
		if(y<l||r<x)return 0;
		if(x<=l&&r<=y)return tr->val-tl->val;
		int m=(l+r)/2;
		return query(l,m,tl->l,tr->l,x,y)+query(m+1,r,tl->r,tr->r,x,y);	
	}
	int query(int l,int r,int x,int y){
		return query(1,m,root[l-1],root[r],x,y);
	}
}pst;

void init_land(int _n,int _m,int p,vector<int> a,vector<int> b){
	n=_n,m=_m;  
	for(int i=2;i<X;i++){
		if(not_prime[i])continue;
		hsh[i]=rng();
		for(int j=i*2;j<X;j+=i){
			not_prime[j]=true;
			int cnt=0;
			for(int x=j;x%i==0;x/=i){
				hsh[j]^=hsh[i];
			}
		}
	}
	for(int i=0;i<n;i++){
		posa[hsh[a[i]]].emplace_back(i+1);
		vals.emplace_back(hsh[a[i]]);
	}
	for(int i=0;i<m;i++){
		posb[hsh[b[i]]].emplace_back(i+1);
		vals.emplace_back(hsh[b[i]]);
	}
	sort(vals.begin(),vals.end());
	vals.erase(unique(vals.begin(),vals.end()),vals.end());
	for(auto x:vals){
		if(posa.count(x)==0||posb.count(x)==0){
			continue;
		}
		auto &pa=posa[x];
		auto &pb=posb[x];
		if(pa.size()<=S&&pb.size()<=S){
			for(auto i:pa){
				for(auto j:pb){
					pts[i].emplace_back(j);
				}
			}
		}else{
			for(auto i:pa){
				dpa[idx][i]++;
			}
			for(auto i:pb){
				dpb[idx][i]++;
			}
			idx++;
		}
	}
	for(int i=0;i<idx;i++){
		for(int j=1;j<=n;j++){
			dpa[i][j]+=dpa[i][j-1];
		}
	}
	for(int i=0;i<idx;i++){
		for(int j=1;j<=m;j++){
			dpb[i][j]+=dpb[i][j-1];
		}
	}
	pst.build(0);
	for(int i=1;i<=n;i++){
		pst.root[i]=pst.root[i-1];
		for(auto j:pts[i]){
			pst.update(i,i,j);
		}
	}
}

long long answer_query(int r1,int c1,int r2,int c2){
	r1++,c1++,r2++,c2++;
	long long ans=pst.query(r1,r2,c1,c2);
	for(int i=0;i<idx;i++){
		long long v1=dpa[i][r2]-dpa[i][r1-1];
		long long v2=dpb[i][c2]-dpb[i][c1-1];
		ans+=v1*v2;
	}
	return ans;
}