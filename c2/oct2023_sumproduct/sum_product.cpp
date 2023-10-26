#include "sum_product.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll mod=1e9+7;
const ll inv=5e8+4;

int sum_product(int n, vector<int> a){
	ll ans=0,sum=0,pw=1,pw2=1;
	for(int i=0;i<n-1;i++)pw2=pw2*2%mod;
	for(int i=0;i<n;i++){
		sum=(sum+pw)*a[i]%mod;
		if(i>0)pw=pw*2%mod;
		if(i<n-1)pw2=pw2*inv%mod;
		ans=(ans+sum*pw2)%mod;
	}
	return ans;
}