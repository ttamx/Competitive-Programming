#include<bits/stdc++.h>
#include "sortingtapes.h"

using namespace std;

vector<int> sort_tapes(int n, vector<int> a, vector<int> b) {
	int k=sqrt(n);
	vector<int> ans(2*n);
	vector<vector<pair<int,int>>> q(k);
	for(int i=0;i<n;i++)q[a[i]/n].push_back({a[i],b[i]});
	for(int i=0;i<=k;i++){
		
	}
	return ans;
}