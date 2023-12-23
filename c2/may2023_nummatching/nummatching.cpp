#include "nummatching.h"
#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> find_matching(int N){
	vector<int> uni,wild;
	vector<bool> used(N);
	vector<vector<int>> ans;
	for(int i=0;i<N-1;i++){
		if(!can_match({i,i+1})){
			uni.emplace_back(i);
			uni.emplace_back(i+1);
			used[i]=used[i+1]=true;
			break;
		}
	}
	for(int i=0;i<N;i++)if(!used[i]){
		if(can_match({i,uni[0]})&&can_match({i,uni[1]})){
			wild.emplace_back(i);
			used[i]=true;
		}
	}
	for(int i=0;i<N;i++)if(!used[i]){
		uni.emplace_back(i);
		if(can_match(uni))uni.pop_back();
		else used[i]=true;
	}
	for(int i=0;i<N;i++)if(!used[i]){
		int l=0,r=uni.size()-1;
		while(l<r){
			int m=(l+r)/2;
			vector<int> res={i};
			for(int j=l;j<=m;j++)res.emplace_back(uni[j]);
			if(can_match(res))r=m;
			else l=m+1;
		}
		ans.push_back({i,uni[l]});
		uni.erase(uni.begin()+l);
	}
	for(auto x:uni){
		ans.push_back({x,wild.back()});
		wild.pop_back();
	}
	for(int i=0;i<wild.size();i+=2)ans.push_back({wild[i],wild[i+1]});
	return ans;
}