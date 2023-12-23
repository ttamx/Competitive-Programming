#include "dungeons.cpp"
#include <vector>
#include <cassert>
#include <cstdio>

static int nn, q;
static std::vector<int> ss, pp, z;
static std::vector<int> ww, lll, x;
static std::vector<long long> answer;

int main() {
	assert(scanf("%d %d", &nn, &q) == 2);
	ss.resize(nn);
	pp.resize(nn);
	ww.resize(nn);
	lll.resize(nn);
    x.resize(q);
    z.resize(q);
    answer.resize(q);

	for (int i = 0; i < nn; i++) {
		assert(scanf("%d", &ss[i]) == 1);
	}
	for (int i = 0; i < nn; i++) {
		assert(scanf("%d", &pp[i]) == 1);
	}
	for (int i = 0; i < nn; i++) {
		assert(scanf("%d", &ww[i]) == 1);
	}
	for (int i = 0; i < nn; i++) {
		assert(scanf("%d", &lll[i]) == 1);
	}


    init(nn, ss, pp, ww, lll);

    for (int i = 0; i < q; i++) {
		assert(scanf("%d %d", &x[i], &z[i]) == 2);
		answer[i] = simulate(x[i], z[i]);
    }
    fclose(stdin);

    for (int i = 0; i < q; i++) {
        printf("%lld\n", answer[i]);
    }
    fclose(stdout);
    return 0;
}
