#include "triples.h"
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll count_triples(vector<int> a){
	int n=a.size();
	int root=-1;
	vector<int> st,lch(n,-1),rch(n,-1);
	for(int i=0;i<n;i++){
		while(!st.empty()&&a[st.back()]<a[i]){
			st.pop_back();
		}
		(st.empty()?root:rch[st.back()])=i;
		st.emplace_back(i);
	}
	int ans=0;
	assert(root!=-1);
	function<void(int,int,int)> dfs=[&](int u,int l,int r){
		if(u==-1)return;
		dfs(lch[u],l,u-1);
		dfs(rch[u],u+1,r);
		if(u-l<r-u){
			for(int i=l;i<u;i++){
				int x=a[i];
				int y=a[u]-x;
				if(u-i==x){
					if(i+y<n&&a[i+y]==y){
						ans++;
					}
				}else if(u-i==y){
					if(i+x<n&&a[i+x]==y){
						ans++;
					}
				}
			}
		}else{

		}
	};
	return 0ll;
}

vector<int> construct_range(int M,int K){
	return {1, 1, 1};
}
