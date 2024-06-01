#include "secret.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const int K=1<<18;
const ll INF=LLONG_MAX/2;

int n,m;
int a[N];
ll qs[N],qs2[N];
set<int> s;

struct SegTree{
	struct Node{
		int l,r;
		Node():l(m),r(-1){}
		Node(int x):l(x),r(x){};
		Node(int _l,int _r):l(_l),r(_r){};
		friend Node operator+(Node l,Node r){
			return Node(min(l.l,r.l),max(l.r,r.r));
		}
	}t[K];
	void build(int l,int r,int i){
		if(l==r)return void(t[i]=Node(a[l]));
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		t[i]=t[i*2]+t[i*2+1];
	}
	void build(){
		build(0,n-1,1);
	}
	Node query(int l,int r,int i,int x,int y){
		if(y<l||r<x)return Node();
		if(x<=l&&r<=y)return t[i];
		int m=(l+r)/2;
		return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
	}
	Node query(int x,int y){
		return query(0,n-1,1,x,y);
	}
}seg;

struct Persist{
    struct Node;
    using Ptr = Node*;
    struct Node{
        ll val;
        Ptr l,r;
        Node(ll val):val(val),l(nullptr),r(nullptr){}
    };
    Ptr rt[N];
    void update(int l,int r,Ptr &t,Ptr k,int x,ll v){
		if(!k)k=new Node(0);
        t=new Node(*k);
        t->val+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,k->l,x,v);
        else update(m+1,r,t->r,k->r,x,v);
    }
    void update(int k,int t,int x,ll v){
        update(0,m-1,rt[t],rt[k],x,v);
    }
    ll query(int l,int r,Ptr tl,Ptr tr,int x,int y){
		if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return tr->val-tl->val;
        int m=(l+r)/2;
        return query(l,m,tl->l,tr->l,x,y)+query(m+1,r,tl->r,tr->r,x,y);
    }
    ll query(int l,int r,int x,int y){
        return query(0,m-1,rt[l-1],rt[r],x,y);
    }
}pst;

void init(int _n,int _m,vector<int> A){
	n=_n,m=_m;
	for(int i=0;i<n;i++)a[i]=A[i];
	seg.build();
	for(int i=1;i<n;i++){
		int d=abs(a[i]-a[i-1]);
		qs[i]=qs[i-1]+d;
		qs2[i]=qs2[i-1]+min(d,m-d);
	}
	pst.rt[0]=new Persist::Node(0);
	for(int i=0;i<n;i++)pst.update(i,i+1,a[i],1);
}

void toggle(int R){
	if(!s.emplace(R).second)s.erase(R);
}

ll query(int S,int T){
	if(s.empty())return qs2[T]-qs2[S];
	auto res=seg.query(S,T);
	auto itl=s.lower_bound(res.l);
	auto itr=s.lower_bound(res.r);
	if(itl!=s.end()&&*itl<res.r&&itr!=s.begin()&&*(--itr)>=res.l){
		int l=*itr,r=*itr;
		if(pst.query(S,T+1,l+1,r)>0)return -1LL;
	}
  	return qs[T]-qs[S]; 
}
