#include <stdio.h>
#include <vector>
#include <cassert>
#include "war.cpp"

int main() {
    int N,Q;
    std::vector<int> A,B,W;

    assert(scanf("%d%d",&N,&Q)==2);

    for (int i=0; i<N-1; ++i) {
        int a,b,w;
        assert(scanf("%d%d%d",&a,&b,&w)==3);
        A.push_back(a);
        B.push_back(b);
        W.push_back(w);
    }

    init(N,A,B,W);

    for (int i=0; i<Q; ++i) {
        int mode,x;
        assert(scanf("%d%d",&mode,&x));
        assert(1<=mode && mode<=3);
        
        switch (mode) {
        case 1:
            toggle_hospital(x);
            break;
        case 2:
            toggle_road(x);
            break;
        case 3:
            printf("%lld\n",nearest_hospital(x));
            break;
        }
    }
}