#include "triplets.cpp"
#include <cstdio>

int main()
{
  int N,M;
  int tmp;
  std::vector<int> C;
  std::vector<int> U;
  std::vector<int> V;

  tmp = scanf("%d %d",&N,&M);

  for(int j=0; j<N; j++) {
    int c;
    tmp = scanf("%d",&c);
    C.push_back(c);
  }

  for(int i=0; i<M; i++) {
    int u,v;
    tmp = scanf("%d %d",&u,&v);
    U.push_back(u);
    V.push_back(v);
  }

  printf("%d\n", count_triplets(N, U, V, C));
  
  return 0;
}

