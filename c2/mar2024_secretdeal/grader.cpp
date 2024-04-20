#include "secretdeal.cpp"

#include <cstdio>

int main()
{
  int N,M,K,L;
  std::vector<int> A;
  std::vector<int> B;
  std::vector<int> W;

  scanf("%d %d %d %d",&N,&M,&K,&L);
  for(int i=0; i<M; i++) {
    int a,b;
    scanf("%d %d",&a,&b);
    A.push_back(a);
    B.push_back(b);
  }
  for(int i=0; i<N; i++) {
    int w;
    scanf("%d",&w);
    W.push_back(w);
  }
  printf("%d\n", make_deal(N,M,K,L,
			   A,B,
			   W));
}
