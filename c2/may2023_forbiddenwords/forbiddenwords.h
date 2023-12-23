#ifndef __FORBIDDEN_H_INCLUDED__
#define __FORBIDDEN_H_INCLUDED__

#include <vector>

std::vector<std::pair<int,int>> alice(int M, int N, int K, long long X, 
				      std::vector<std::pair<int,int>> F);
  

long long bob(int M, std::vector<std::pair<int,int>> W);

#endif
