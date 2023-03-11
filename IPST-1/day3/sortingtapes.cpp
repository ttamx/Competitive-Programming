#include "sortingtapes.h"
#include <bits/stdc++.h>

using namespace std;

std::vector<int> sort_tapes(int N, std::vector<int> A, std::vector<int> B) {
  std::vector<int> C;
  int i=0,j=0;
  while(i<N&&j<N){
  	if(compare(A[i],B[j])){
  		C.push_back(A[i]);
  		i++;
  	}else{
  		C.push_back(B[j]);
  		j++;
  	}
  }
  while(i<N){
  	C.push_back(A[i]);
  	i++;
  }
  while(j<N){
  	C.push_back(B[j]);
  	j++;
  }
  return C;
}