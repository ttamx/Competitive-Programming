#include "september.cpp"

#include <cassert>
#include <cstdio>
#include <vector>

void taskcase() {
	int N, M;
	assert(2 == scanf("%d%d", &N, &M));
	
	std::vector<int> F(N);
	F[0] = -1;
	for (int i = 1; i < N; ++i)
  		assert(1 == scanf("%d", &F[i]));
	
	std::vector<std::vector<int>> S(M, std::vector<int>(N - 1));
	for (int i = 0; i < M; ++i)
		for (int j = 0; j < N - 1; ++j)
  			assert(1 == scanf("%d", &S[i][j]));
  	
	printf("%d\n", solve(N, M, F, S));
}

int main() {
	int T;
	assert(1 == scanf("%d", &T));
	while(T--) taskcase();
	return 0;
}
