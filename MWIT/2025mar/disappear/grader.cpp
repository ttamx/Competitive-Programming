#include <cstdio>
#include <cassert>
#include <cstdlib>
#include <vector>
#include "disappear.cpp"

namespace grader{
  int N,M,K, num_queries;
  std::vector<bool> next_to;
}

using namespace grader;

bool detect(std::vector<int> S){
  std::vector<bool> found(N);
  num_queries++;
  bool b1 = false, b2 = false;
  for(auto &a : S){
    if(a < 0 || a > N-1){
      printf("Invalid Query : Out of Range\n");
      exit(1);
    }
    if(found[a]){
      printf("Invalid Query : Duplicate Elements\n");
      exit(1);
    }
    found[a] = true;
    if(a == K){b1 = true;}
    if(next_to[a]){b2 = true;}
  }
  return b1 && b2;
}

int main(){
  assert(scanf("%d %d %d",&N, &M, &K) == 3);
  
  next_to = std::vector<bool>(N,false);
  std::vector<int> U(M), V(M);
  for(int i = 0; i < M; i++){
    assert(scanf("%d %d",&U[i], &V[i])==2);

    if(U[i] == K){
      next_to[V[i]] = true;
    }
    if(V[i] == K){
      next_to[U[i]] = true;
    }
  }
  fclose(stdin);

  num_queries = 0;
  int ans = miku(N, M, U, V);

  printf("%d\n", ans);
  printf("Used %d queries\n", num_queries);
  fclose(stdout);

  return 0;
}
