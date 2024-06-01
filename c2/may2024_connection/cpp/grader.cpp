#include "connection.cpp"
#include <vector>
#include <stdio.h>
#include <assert.h>

int main() {
    int N,M;
    assert(scanf("%d%d",&N,&M)==2);
    
    std::vector<int> A,B,H;

    for (int i=0; i<N; ++i) {
        int x;
        assert(scanf("%d",&x)==1);
        H.push_back(x);
    }

    for (int i=0; i<M; ++i) {
        int a,b;
        assert(scanf("%d%d",&a,&b)==2);
        A.push_back(a);
        B.push_back(b);
    }

    printf("%d",recommended_stations(N,M,H,A,B));
}