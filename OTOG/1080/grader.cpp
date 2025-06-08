#include "space.cpp"
#include <cassert>
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int goToSpace(int, int, int, vector<pair<int, int>>);

int main(){
    int N;
    assert(scanf("%d", &N) == 1);

    int M;
    assert(scanf("%d", &M) == 1);

    int X;
    assert(scanf("%d", &X) == 1);

    int K;
    assert(scanf("%d", &K) == 1);

    vector<pair<int, int>> V(X);
    for (int i = 0; i < X; i++) {
        assert(scanf("%d %d", &V[i].first, &V[i].second) == 2);
    }

    int answer = goToSpace(N, M, K, V);

    printf("%d", answer);
}
