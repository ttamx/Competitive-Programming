#include <stdio.h>
#include <stdlib.h>
#include "game.cpp"

#define fail(s, x...) do { \
		fprintf(stderr, s "\n", ## x); \
		exit(1); \
	} while(0)

#define MAX_SIZE 1000000000
#define MAX_N 272000

int main() {
	int R, C, N;
    int P, Q, U, V;
    long long K;
    int i, type;
	int res;

	FILE *f = fopen("game.in", "r");
	if (!f)
		fail("Failed to open input file.");

	res = fscanf(f, "%d", &R);
	res = fscanf(f, "%d", &C);
	res = fscanf(f, "%d", &N);

    init(R, C);

	for (i = 0; i < N; i++) {
        res = fscanf(f, "%d", &type);
        if (type == 1) {
		    res = fscanf(f, "%d%d%lld", &P, &Q, &K);
            update(P, Q, K);
        } else if (type == 2) {
		    res = fscanf(f, "%d%d%d%d", &P, &Q, &U, &V);
            printf("%lld\n", calculate(P, Q, U, V));
        } else
			fail("Invalid action type in input file.");
	}
	fclose(f);

	return 0;
}
