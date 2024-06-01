#include "buffet.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

ll min_leftover(int N,vector<int> A) {
	int h=A[0];
	ll ans=LLONG_MAX;
	for(int i=0;i<N;i++){
		h=min(h,A[i]);
		A[i]-=h;
		int h2=A[N-1];
		ll tot=0;
		for(int j=N-1;j>=0;j--){
			h2=min(h2,A[j]);
			tot+=A[j]-h2;
		}
		ans=min(ans,tot);
	}
	return ans;
}
