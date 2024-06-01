#include "lightcolors.cpp"
#include <vector>
#include <cstdio>

int main()
{
  int dummy;
  int N,M;
  std::vector<int> A;
  std::vector<int> B;

  dummy = scanf("%d %d",&N,&M);
  for(int i=0; i<M; i++) {
    int u,v;
    scanf("%d %d",&u,&v);
    A.push_back(u);
    B.push_back(v);
  }

  std::vector<int> colors = lightcolors(N,M,A,B);

  for(int c : colors) {
    printf("%d\n",c);
  }
}
