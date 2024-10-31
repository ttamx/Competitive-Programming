#include "particle.cpp"
#include <cstdio>
#include <vector>
using std::vector;
int main() {
    int N,Q;
    int tmp;
    scanf("%d %d",&N,&Q);
    init(N);
    for(int i = 0;i < Q;i++) {
        int type,L,R;
        tmp = scanf("%d %d %d",&type,&L,&R);
        if(type==1) {
            int P;
            tmp = scanf("%d",&P);
            generateParticle(L,R,P);
        }
        else if(type==2) {
            printf("%lld\n",countSize(L,R));
        }
        else {
            printf("%d\n",bestPartition(L,R));
        }
    }
    return 0;
}