#include "gap.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

long long findGap(int T, int n){
	ll mn,mx;
	MinMax(1,1e18,&mn,&mx);
	if(T==1){
		vector<ll> a(n);
		a[0]=mn,a[n-1]=mx;
		if(n==2)return mx-mn;
		ll ans=0;
		for(int l=1,r=n-2;l<=r;l++,r--){ 
			MinMax(a[l-1]+1,a[r+1]-1,&a[l],&a[r]);
			ans=max({ans,a[l]-a[l-1],a[r+1]-a[r]});
		}
		return ans;
	}
	ll ans=(mx-mn+n-2)/(n-1);
	for(ll l=mn,r=mx,p=mn;l+1<r;){
		MinMax(l+1,min(l+ans,r),&mn,&mx);
		l+=ans+1;
		if(mn!=-1)ans=max(ans,mn-p),p=mx;
	}
	return ans;
}