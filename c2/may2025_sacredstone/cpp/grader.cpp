#include "sacredstone.cpp"
#include <vector>
#include <stdio.h>
#include <assert.h>

int main() {
    int N;
    assert(scanf("%d",&N)==1);

    std::vector<int> A(N),C(N+1);
    for (int i=0; i<N; ++i) assert(scanf("%d",&A[i])==1);
    for (int i=0; i<=N; ++i) assert(scanf("%d",&C[i])==1);

    long long result=sacredstone(N,A,C);
    printf("%lld\n",result);
}