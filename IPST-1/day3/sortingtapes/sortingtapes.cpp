#include "sortingtapes.h"
#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int l[N],r[N];
vector<int> res[N];

std::vector<int> sort_tapes(int N, std::vector<int> A, std::vector<int> B) {
  std::vector<int> C;
  for(auto i:A)cout << i << ' ';
  	cout << '\n';
  for(auto i:B)cout << i << ' ';
  	cout << '\n';
  for(int i=0;i<N;i++){
  	int l=0,r=N;
  	if(i%2==0){
  	for(int j=N;j<2*N;j++){
  		int idx=lower_bound(B.begin(),B.end(),j)-B.begin();
  		if(compare(i,j)){
  			cout << idx << '\n';
  			r=min(r,idx);
  		}
  	}
  	}
  	else{
  	for(int j=2*N-1;j>=N;j--){
  		int idx=lower_bound(B.begin(),B.end(),j)-B.begin();
  		if(compare(i,j)){
  			r=min(r,idx);
  		}
  	}
	}
	cout << i << ' ' << r << '\n';
  	res[r].push_back(i);
  }
  for(int i=0;i<N;i++){
  	for(auto j:res[i])C.push_back(j);
  	C.push_back(B[i]);
  }
  for(auto i:res[N])C.push_back(i);
  return C;
}