#include "immigration.cpp"
#include <stdio.h>
#include <assert.h>
#include <vector>

int main() {
    int N;
    std::vector<int> A;

    assert(scanf("%d",&N)==1);
    for (int i=0; i<N; ++i) {
        int x;
        assert(scanf("%d",&x));
        assert(1<=x && x<=N);
        A.push_back(x);
    }

    int k=immigration(N,A);
    printf("%d\n",k);
}