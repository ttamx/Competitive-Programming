#include <vector>
#include <stdio.h>
#include "OES.cpp"

int main() {
    int N;
    std::vector<int> U,V,L;

    scanf("%d",&N);
    for (int i=0; i<N-1; ++i) {
        int u,v,l;
        scanf("%d%d%d",&u,&v,&l);
        U.push_back(u);
        V.push_back(v);
        L.push_back(l);
    }

    printf("%d\n",machinepower(N,U,V,L));
}