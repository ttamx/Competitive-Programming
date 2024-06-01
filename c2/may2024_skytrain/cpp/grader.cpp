#include <stdio.h>
#include <vector>
#include <assert.h>
#include "skytrain.cpp"

int main() {

    int N,M,X,Y;
    long long K;
    assert(scanf("%d%d%lld%d%d",&N,&M,&K,&X,&Y)==5);

    std::vector<int> A,B,W;

    for (int i=0; i<M; ++i) {
        int a,b,w;
        assert(scanf("%d%d%d",&a,&b,&w)==3);
        A.push_back(a);
        B.push_back(b);
        W.push_back(w);
    }

    long long res=min_total_cost(N,M,A,B,W,K,X,Y);

    printf("%lld",res);
}