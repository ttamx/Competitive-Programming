#include"sailing.h"
#include<bits/stdc++.h>

using namespace std;

const int BIT=33;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int set_sail(){
	for(int k=2;k<BIT;k<<=1){
		vector<int> mem(k+1);
		for(int i=1;i<=k;i++){
			mem[i]=sail_forward()^1;
			flag();
		}
		for(int i=1;i<=k;i++)if(sail_backward()!=mem[k-i])return i;
	}
	bitset<BIT> hsh=0,cur=0;
	hsh=rng();
	for(int i=BIT-1;i>=0;i--)if(sail_forward()!=(hsh[i]))flag();
	for(int i=BIT-1;i>=0;i--)cur[i]=sail_forward();
	int ans=BIT;
	while(cur!=hsh){
		cur<<=1;
		cur[0]=sail_forward();
		ans++;
	}
	return ans;
}