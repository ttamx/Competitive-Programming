#include "Bruno.h"
#include<bits/stdc++.h>

using namespace std;

namespace {

int n,l;

}  // namespace

void init(int N, int L) {
	n=N,l=L;
}

int bruno(string s){
	if(n==l)return 1;
	vector<int> a;
	for(int i=0;i+2<l;i++){
		if(s[i]==s[i+1]&&s[i+1]!=s[i+2]){
			a.emplace_back(i);
			if(a.size()==2)break;
		}
	}
	cerr << a.size() << "\n";
	for(auto x:a)cerr << x << " ";
	cerr << "\n";
	int dif=a[1]-a[0];
	int pos=2+127*128/2-dif*(dif+1)/2;
	cerr << pos-a[0] << " " << dif << "\n";
	return pos-a[0];
}

