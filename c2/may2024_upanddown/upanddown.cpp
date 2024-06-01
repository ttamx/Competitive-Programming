#include"upanddown.h"
#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int X=4e5+5;
const int MOD=1e9+7;

int n;
int a[N];
int ans;

struct Fenwick{
	int t[X],val[X];
	void update(int i,int v){
		if(v<0)v+=MOD;
		val[i]+=v;
		if(val[i]>=MOD)val[i]-=MOD;
		for(;i<X;i+=i&-i){
			t[i]+=v;
			if(t[i]>=MOD)t[i]-=MOD;
		}
	}
	int query(int i){
		int res=0;
		for(;i>0;i-=i&-i){
			res+=t[i];
			if(res>=MOD)res-=MOD;
		}
		return res;
	}
}fa,fb,fc,fd,fe;

void update(int x){
	fc.update(x,(1LL*fb.val[x]*fd.val[x]-fc.val[x])%MOD);
}

long long upanddown(int _n,vector<int> _a){
	n=_n;
	for(int i=1;i<=n;i++)a[i]=_a[i-1];
	for(int i=1;i<=n;i++){
		fb.update(a[i],fa.query(a[i]-1));
		fa.update(a[i],1);
	}
	for(int i=n;i>=1;i--){
		fa.update(a[i],-1);
		fb.update(a[i],-fa.query(a[i]-1));
		update(a[i]);
		ans=(ans+1LL*fb.query(a[i]-1)*fd.query(a[i]-1)-fc.query(a[i]-1)+MOD)%MOD;
		fd.update(a[i],fe.query(a[i]-1));
		fe.update(a[i],1);
		update(a[i]);
	}
	return ans;
}
