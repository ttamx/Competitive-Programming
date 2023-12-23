#include "sum_product.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll mod=1e9+7;

ll pw[N];

int sum_product(int n, vector<int> a){
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	ll ans=0,sum=0;
	for(int i=0;i<n;i++){
		sum=(sum+pw[max(i-1,0)])*a[i]%mod;
		ans=(ans+sum*pw[max(n-i-2,0)])%mod;
	}
	return ans;
}