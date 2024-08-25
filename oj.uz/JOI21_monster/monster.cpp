#include "monster.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> Solve(int n){
	mt19937 rng(777);
	map<pair<int,int>,bool> memo;
	auto query=[&](int x,int y){
		if(memo.count({x,y}))return memo[{x,y}];
		bool res=Query(x,y);
		memo[{x,y}]=res;
		memo[{y,x}]=!res;
		return res;
	};
	vector<int> a(n),b(n);
	function<void(int,int)> msort=[&](int l,int r){
		if(l==r)return;
		shuffle(a.begin()+l,a.begin()+r+1,rng);
		int m=(l+r)/2;
		msort(l,m);
		msort(m+1,r);
		for(int i=l,j=m+1,p=l;p<=r;p++){
			if(j>r||(i<=m&&!query(a[i],a[j]))){
				b[p]=a[i++];
			}else{
				b[p]=a[j++];
			}
		}
		for(int i=l;i<=r;i++)a[i]=b[i];
	};
	iota(a.begin(),a.end(),0);
	msort(0,n-1);
	auto check=[&](int x){
		int cnt=0;
		for(int i=0;i<min(n,10);i++){
			if(i==x)continue;
			if(query(a[x],a[i])){
				cnt++;
				if(cnt>1){
					return false;
				}
			}
		}
		return true;
	};
	bool ok0=check(0),ok1=check(1);
	int st=-1;
	if(ok0){
		if(ok1){
			for(int i=2;i<min(n,10);i++){
				bool v0=query(a[i],a[0]);
				bool v1=query(a[i],a[1]);
				assert(v0||v1);
				if(v0^v1){
					st=v1;
					break;
				}
			}
		}else{
			st=0;
		}
	}
	if(st==-1){
		st=2;
		while((query(a[st-1],a[st])||query(a[st],a[0]))){
			st++;
			assert(st<n);
		}
	}
	reverse(a.begin(),a.begin()+st+1);
	for(int i=st+1;i<n;i++){
		int j=i;
		while(!query(a[i-1],a[j])){
			j++;
			assert(j<n);
		}
		reverse(a.begin()+i,a.begin()+j+1);
		i=j;
	}
	vector<int> ans(n);
	for(int i=0;i<n;i++)ans[a[i]]=i;
	return ans;
}
