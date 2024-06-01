#include <cstdio>
#include <vector>
#include "mountain.cpp"

signed main(int argc, char *argv[]) {
	int N, Q, S, X;
	scanf("%d %d", &N, &Q);
	std::vector<int> A(N);
	for(int i=0; i<N; ++i) {
		scanf("%d", &A[i]);
	}
	std::vector<int> C(N);
	for(int i=0; i<N; ++i) {
		scanf("%d", &C[i]);
	}
	initialize(N, A, C);
	while(Q--) {
		scanf("%d %d", &S, &X);
		printf("%lld\n", race_cost(S, X));
	}
	return 0;
}
