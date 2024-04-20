#include "ancient2.h"
#include<bits/stdc++.h>

using namespace std;

string solve_left(int n){
	string ans(n,'0');
	int m=n+2;
	vector<int> a(m),b(m);
	a[n]=b[n]=n;
	a[n+1]=b[n+1]=n+1;
	for(int i=0;i<n;i++){
		a[i]=n;
		b[i]=n+1;
	}
	for(int i=0;i<n;i++){
		int res=Query(m,a,b);
		ans[i]=res-n+'0';
		a[i]=b[i]=i+1;
	}
	return ans;
}

string solve_right(int n){
	string ans(n,'0');
	string suf="";
	for(int i=0;i<n;i++){
		suf="1"+suf;
		int m=i+2;
		vector<vector<int>> a(2,vector<int>(m));
		for(int j=0;j<m;j++){
			for(int c=0;c<2;c++){
				int sz=min(j+1,i+1);
				while(sz>0&&(suf.substr(j-sz+1,sz-1)+char('0'+c))!=suf.substr(0,sz)){
					sz--;
				}
				a[c][j]=sz;
			}
		}
		int res=Query(m,a[0],a[1]);
		res=(res==i+1);
		ans[n-i-1]=res+'0';
		suf[0]=res+'0';
	}
	return ans;
}

string Solve(int n) {
	return solve_left(n/2)+solve_right((n+1)/2);
}