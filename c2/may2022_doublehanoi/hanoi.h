#ifndef __HANOI_H_INCLUDED__
#define __HANOI_H_INCLUDED__

#include <vector>

long long hanoi(int N,
	        std::vector<int> S0, std::vector<int> S1, std::vector<int> S2,
   	        std::vector<int> T0, std::vector<int> T1, std::vector<int> T2);

#endif
