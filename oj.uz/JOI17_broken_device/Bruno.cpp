#include "Brunolib.h"
#include<bits/stdc++.h>

using namespace std;

long long Bruno(int n,int a[]){
	mt19937_64 rng(0);
	uint64_t ans=0;
	for(int i=0;i<n;i++){
		uint64_t val=rng();
		if(a[i]){
			ans^=val;
		}
	}
  	return ans;
}