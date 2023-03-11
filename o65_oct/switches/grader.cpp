#include "switches_v2.cpp"
#include <vector>
#include <cassert>
#include <cstdio>

int main(){
	int N, M, K;
	assert(scanf("%d %d %d", &N, &M, &K) == 3);
	std::vector<int> A(N), L(M), R(M), C(M);
	for(int i = 0; i < N; i++){
		assert(scanf("%d", &A[i]) == 1);
	}
	for(int i = 0; i < M; i++){
		assert(scanf("%d %d %d", &L[i], &R[i], &C[i]) == 3);
	}
	printf("%lld\n", minimum_energy(N, M, K, A, L, R, C));
}
