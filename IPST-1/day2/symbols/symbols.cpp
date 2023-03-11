#include "symbols.h"
#include<bits/stdc++.h>

using namespace std;
// edit this file as you like

typedef long long ll;

const int N=2e5+5;
const int K=1<<19;
const ll mod=20232566;

int n,q;
bool impossible=false;
ll poww[N],P[30][30];
int ans,sz;
bool used[N];
set<pair<int,int>> s;

struct segtree{
	ll tree[K];
	void build(int l,int r,int i){
		if(l==r){
			tree[i]=26;
			return;
		}
		int m=(l+r)/2;
		build(l,m,i*2);
		build(m+1,r,i*2+1);
		tree[i]=(tree[i+2]*tree[i*2+1])%mod;
	}
	void update(int l,int r,int i,int x,int v){
		if(x<l||x>r)return;
		if(l==r){
			tree[i]=v;
			return;
		}
		int m=(l+r)/2;
		update(l,m,i*2,x,v);
		update(m+1,r,i*2+1,x,v);
		tree[i]=(tree[i*2]*tree[i*2+1])%mod;
	}
}seg;

struct fenwick{
	int f[N];
	void add(int i,int v){
		i++;
		while(i<N){
			f[i]=max(f[i],v);
			i+=i&-i;
		}
	}
	int read(int i){
		int ret=-1;
		i++;
		while(i){
			ret=max(ret,f[i]);
			i-=i&-i;
		}
		return ret;
	}
}cover;

void explore_site(int N, int Q) {
  	n = N;
  	q = Q;
  	seg.build(0,n-1,1);
 	poww[0]=1;
  	for(int i=1;i<=n;i++){
  		poww[i]=(poww[i-1]*26)%mod;
  	}
  	for(int i=0;i<=26;i++){
  		P[i][0]=1;
  		for(int j=1;j<=i;j++){
  			P[i][j]=(P[i][j-1]*(i-j+1))%mod;
  		}
  	}
  	ans=1;
  	sz=n;
  	for(int i=1;i<=n;i++)cover.f[i]=-1;
}

int retrieve_notes(int L, int R) {
	if(R-L>25)impossible=true;
	if(impossible)return 0;
	if(cover.read(L)>=R)return ans;
	auto it=s.lower_bound({L,0});
	while(it!=s.end()&&it->first<=R){
		if(it->second<=R){
			it=s.erase(it);
		}
		else it=s.lower_bound({it->first+1,0});
	}
	cover.add(L,R);
	for(int i=L;i<=R;i++){
		if(used[i])continue;
		used[i]=true;
		sz--;
	}
	ll tmp=1;
	s.insert({L,R});
	seg.build(0,n-1,1);
	it=s.begin();
	while(it!=s.end()){
		if(it!=s.begin()){
			int prevR=prev(it)->second;
			if(it->first>prevR){
				int cnt=26;
				for(int i=it->first;i<=it->second;i++){
					tmp=(tmp*cnt--)%mod;
				}
			}else{
				int cnt=26-(prevR-it->first+1);
				for(int i=prevR+1;i<=it->second;i++){
					tmp=(tmp*cnt--)%mod;
				}
			}
		}else{
			int cnt=26;
			for(int i=it->first;i<=it->second;i++){
				tmp=(tmp*cnt--)%mod;
			}
		}
		it++;
	}
	ans=(tmp*poww[sz])%mod;
 	return ans;
}