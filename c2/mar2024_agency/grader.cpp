#include <vector>
#include <cstdio>
#include "agency.cpp"
int main() {
    int N,M,Q;
    scanf("%d%d%d",&N,&M,&Q);
    std::vector<int> T(M);
    std::vector<std::vector<int>> Road(N,std::vector<int>(3));
    for(int i = 0;i < N;i++) {
        scanf("%d%d%d",&Road[i][0],&Road[i][1],&Road[i][2]);
    }
    for(int i = 0;i < M;i++) {
        scanf("%d",&T[i]);
    }
    init(N,T,Road);
    int L,R,X;
    for(int i = 0;i < Q;i++) {
        scanf("%d%d%d",&L,&R,&X);
        printf("%lld\n",min_distance(L,R,X));
    }
} 