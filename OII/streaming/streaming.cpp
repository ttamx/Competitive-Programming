#include <bits/stdc++.h>
#include "grader.cpp"

using namespace std;

typedef long long ll;

ll bfs(int N, ll K, vector<int> P, vector<int> F){
	ll ans=0;
	vector<pair<ll,ll>> a;
	for(int i=0;i<N;i++)a.emplace_back(P[i],F[i]);
	sort(a.rbegin(),a.rend());
	priority_queue<ll> pq;
	ll sum=0;
	for(auto [p,f]:a){
		pq.emplace(f);
		sum+=f;
		while(!pq.empty()&&(pq.top()>=p||sum>K)){
			sum-=pq.top();
			pq.pop();
		}
		ans=max(ans,p*(ll)pq.size()-sum);
	}
	return ans;
}