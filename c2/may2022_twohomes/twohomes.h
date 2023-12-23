#ifndef __TWOHOMES_H_INCLUDED__
#define __TWOHOMES_H_INCLUDED__

#include <vector>

std::pair<int,int> find_homes(int N, int M,
			      std::vector<std::vector<int>> R);

bool is_reachable(std::vector<int> C);

#endif
