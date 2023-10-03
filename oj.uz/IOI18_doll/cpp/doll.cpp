#include "doll.h"
#include<bits/stdc++.h>
 
using namespace std;
 
void create_circuit(int m,vector<int> a) {
	int n = a.size();
	a.emplace_back(0);
	vector<int> c(m+1);
	vector<int> x,y;
	int lv=0;
	while((1<<lv)<n)lv++;
	int sz=1<<lv;
	vector<int> t(2<<lv),id(2<<lv,m+1),pos(1<<lv);
	for(int i=0;i<1<<lv;i++)for(int j=0;j<lv;j++)if((i>>j)&1)pos[i]+=1<<(lv-j-1);
	map<int,int> mp;
	for(int i=0;i<n;i++)t[(2<<lv)-1-i]=1,mp[pos[(1<<lv)-i-1]];
	int idx=0;
	for(auto &[x,y]:mp)y=++idx;
	for(int i=0;i<n;i++)id[(2<<lv)-1-i]=a[mp[pos[(1<<lv)-i-1]]];
	int cnt=0;
	for(int i=(1<<lv)-1;i>=1;i--){
		t[i]=t[i*2]+t[i*2+1];
		if(t[i]){
			x.emplace_back(id[i*2]);
			y.emplace_back(id[i*2+1]);
			id[i]=-x.size();
		}
	}
	for(auto &i:x)if(i>m)i=id[1];
	for(auto &i:y)if(i>m)i=id[1];
	c[0]=a[0];
	for(int i=1;i<=m;i++)c[i]=id[1];
	answer(c,x,y);
}