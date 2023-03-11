#include "community.cpp"
#include <vector>
#include <cstdio>

int main(){
  int N;
  scanf("%d",&N);
  std::vector<int> w;
  w.reserve(N);
  for(int i = 0; i < N; i++){
    int x;
    scanf("%d",&x);
    w.push_back(x);
  }
  printf("%d\n", minimum_cost(N, w));
}
