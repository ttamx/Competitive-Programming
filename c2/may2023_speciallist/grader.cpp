#include "speciallist.cpp"
#include <cstdio>

int main()
{
  int dummy;
  int N,M;
  std::vector<int> P;
  std::vector<int> X;
  std::vector<int> Z;

  dummy = scanf("%d %d", &N, &M);
  P.push_back(-1);
  for(int i=0; i<N-1; i++) {
    int pp;
    dummy = scanf("%d",&pp);
    P.push_back(pp);
  }
  for(int i=0; i<N; i++) {
    int xx;
    dummy = scanf("%d",&xx);
    X.push_back(xx);
  }
  for(int i=0; i<M; i++) {
    int zz;
    dummy = scanf("%d",&zz);
    Z.push_back(zz);
  }
  std::vector<int> res = compute_cost(N,M,P,X,Z);
  for(int r : res) {
    printf("%d\n",r);
  }
}
