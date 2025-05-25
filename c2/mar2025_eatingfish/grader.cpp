#include <cstdio>
#include <vector>

#include "eatingfish.cpp"

signed main(int argc, char *argv[]) {
	int N, Q;
	scanf("%d %d", &N, &Q);
	std::vector<int> S(N);
	for(int i=0; i<N; ++i) {
		scanf("%d", &S[i]);
	}
	init_fish(N, S);
	while(Q--) {
		int O;
		scanf("%d", &O);
		if(O == 1) {
			int P, V;
			scanf("%d %d", &P, &V);
			cast_magic(P, V);
		}
		else {
			int P, L, R;
			scanf("%d %d %d", &P, &L, &R);
			printf("%lld\n", eat_friend(P, L, R));
		}
	}
	return 0;
}
