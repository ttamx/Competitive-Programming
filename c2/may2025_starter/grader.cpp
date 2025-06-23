#include <cstdio>
#include <vector>
#include "starter.cpp"
using std::vector;
int main() {
    int N,Q,tmp;
    tmp = scanf("%d%d",&N,&Q);
    vector<int>A(N),U(N-1),V(N-1),Query(Q);
    for(int i = 0;i < N-1;i++) {
        tmp = scanf("%d",&U[i]);
    }
    for(int i = 0;i < N-1;i++) {
        tmp = scanf("%d",&V[i]);
    }
    for(int i = 0;i < N;i++) {
        tmp = scanf("%d",&A[i]);
    }
    initialize(N,Q,U,V,A);
    long long a,b;
    for(int i = 0;i < Q;i++) {
        tmp = scanf("%d %lld %lld",&Query[i],&a,&b);
        printf("%lld\n",answer(Query[i],a,b));
    }
}