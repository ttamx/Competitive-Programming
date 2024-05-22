#include "Anna.h"
#include<bits/stdc++.h>

using namespace std;

namespace {

}

pair<string,int> anna(int n,string s) {
	vector<int> a(n+4);
	for(int i=0;i<n;i++){
		if(s[i]=='R')a[i]=0;
		if(s[i]=='G')a[i]=1;
		if(s[i]=='B')a[i]=2;
	}
	vector<int> ans(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<3;j++)if(j!=a[i]){
			ans[i]=j;
			break;
		}
	}
	if(n<=130){
		string t="";
		for(auto x:ans)t.push_back("RGB"[x]);
		return make_pair(t,n);
	}
	auto add=[&](int pos){
		for(int i=0;i<3;i++)if(i!=a[pos]){
			for(int j=0;j<3;j++)if(j!=a[pos+1]){
				if(i==j){
					ans[pos]=i;
					ans[pos+1]=j;
					return;
				}
			}
		}
	};
	for(int i=0,d=127;i<n&&d>0;i+=d--){
		add(i);
		for(int j=i+2;j<n&&j<i+d;j++){
			for(int k=0;k<3;k++)if(k!=a[j]){
				if(k!=ans[j-1]){
					ans[j]=k;
					break;
				}
			}
		}
	}
	string t="";
	ans.resize(n);
	for(auto x:ans)t.push_back("RGB"[x]);
	cerr << t << "\n";
	return make_pair(t,min(n,130));
}