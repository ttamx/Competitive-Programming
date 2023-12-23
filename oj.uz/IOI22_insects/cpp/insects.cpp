#include "insects.h"
#include<bits/stdc++.h>

using namespace std;

int min_cardinality(int n){
	vector<int> single,cur;
	for(int i=0;i<n;i++){
		move_inside(i);
		if(press_button()>1){
			cur.emplace_back(i);
			move_outside(i);
		}else{
			single.emplace_back(i);
		}
	}
	int k=single.size();
	int l=1,r=n/k;
	int cnt=k;
	while(l<r){
		int m=(l+r+1)/2;
		vector<int> vl,vr;
		shuffle(cur.begin(),cur.end(),mt19937_64(time(nullptr)));
		for(auto i:cur){
			if(vl.size()+cnt==k*m){
				vr.emplace_back(i);
				continue;
			}
			move_inside(i);
			if(press_button()>m){
				vr.emplace_back(i);
				move_outside(i);
			}else{
				vl.emplace_back(i);
			}
		}
		if(vl.size()+cnt==k*m){
			l=m;
			cnt+=vl.size();
			cur=vr;
		}else{
			r=m-1;
			for(auto i:vl)move_outside(i);
			cur=vl;
		}
	}
	return l;
}