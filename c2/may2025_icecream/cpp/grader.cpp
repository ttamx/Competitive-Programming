#include <vector>
#include <stdio.h>
#include <assert.h>
#include "icecream.cpp"

int main() {
    int N,Q;
    std::vector<int> P;

    assert(scanf("%d%d",&N,&Q)==2);
    for (int i=0; i<N; ++i) {
        int x;
        assert(scanf("%d",&x)==1);
        P.push_back(x);
    }

    initialize(N,Q,P);

    std::vector<long long> ans(Q);

    for (int i=0; i<Q; ++i) {
        int x,l1,r1,l2,r2;
        assert(scanf("%d%d%d%d%d",&x,&l1,&r1,&l2,&r2)==5);
        ans[i] = count_perm(x,l1,r1,l2,r2);
    }

    for (int i=0; i<Q; ++i) printf("%lld\n",ans[i]);
}