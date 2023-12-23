#include "inversion.h"
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

struct fenwick{
	int t[N];
	void add(int i,int v){
		while(i<N)t[i]+=v,i+=i&-i;
	}
	int read(int i){
		int res=0;
		while(i>0)res+=t[i],i-=i&-i;
		return res;
	}
}f;

vector<int> find_permutation(int n, ll inversion) {
	vector<ll> a;
	vector<int> ans(n);
	a.emplace_back(inversion);
	for(int i=1;i<n;i++)a.emplace_back(swap_and_report(0,i));
	for(int i=1;i<=n;i++)f.add(i,1);
	for(int i=n-1;i>=0;i--){
		int pos=(a[i]-a[0]+i)/2+1;
		int l=1,r=n;
		while(l<r){
			int m=(l+r)/2;
			if(f.read(m)>=pos)r=m;
			else l=m+1;
		}
		f.add(l,-1);
		ans[i]=l;
	}
	return ans;
}