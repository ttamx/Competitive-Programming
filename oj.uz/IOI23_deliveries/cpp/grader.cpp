#include "deliveries.cpp"
#include <cassert>
#include <cstdio>
#include <vector>

int main() {
	int N, Q;
	assert(2 == scanf("%d %d", &N, &Q));
	std::vector<int> U(N - 1), V(N - 1);
	for(int j = 0; j + 1 < N; j++)
		assert (1 == scanf("%d", &U[j]));
	for(int j = 0; j + 1 < N; j++)
		assert (1 == scanf("%d", &V[j]));
	std::vector<int> T(N - 1);
	for(int j = 0; j + 1 < N; j++)
		assert (1 == scanf("%d", &T[j]));
	std::vector<int> W(N);
	for(int i = 0; i < N; i++)
		assert (1 == scanf("%d", &W[i]));
	std::vector<int> S(Q);
	std::vector<int> X(Q);
	for(int k = 0; k < Q; k++)
		assert (2 == scanf("%d %d", &S[k], &X[k]));

	fclose(stdin);

	init(N, U, V, T, W);
	std::vector<long long> res(Q);
	for(int k = 0; k < Q; k++)
		res[k] = max_time(S[k], X[k]);

	for(int k = 0; k < Q; k++)
		printf("%lld\n", res[k]);
	fclose(stdout);
	return 0;
}
