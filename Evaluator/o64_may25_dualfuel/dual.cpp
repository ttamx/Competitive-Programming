#include <bits/stdc++.h>
#include "dual.h"

using namespace std;

typedef long long ll;

ll dual_fuel(int n,int v,vector<int> &a, vector<int> &b) {
	deque<pair<int,int>> dq1,dq2;
	ll res=0;
	for(int i=0;i<n;i++){
		while(!dq1.empty()&&dq1.front().second+v<=i)dq1.pop_front();
		while(!dq1.empty()&&dq1.back().first>=a[i])dq1.pop_back();
		dq1.emplace_back(a[i],i);
		res+=dq1.front().first;
		while(!dq2.empty()&&dq2.front().second+v<=i)dq2.pop_front();
		while(!dq2.empty()&&dq2.back().first>=b[i])dq2.pop_back();
		dq2.emplace_back(b[i],i);
		res+=dq2.front().first;
	}
	return res;
}