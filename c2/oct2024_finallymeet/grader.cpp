#include "finallymeet.cpp"
#include <cstdio>
#include <vector>

int N,M;
std::vector<int> U,V;

void read_input()
{
  int dummy;
  dummy = scanf("%d %d",&N,&M);
  for(int i=0; i<M; i++) {
    int u,v;
    dummy = scanf("%d %d",&u,&v);
    U.push_back(u);
    V.push_back(v);
  }
}

int main()
{
  read_input();
  long long res = count_init(N,M,U,V);
  printf("%lld\n",res);
}
