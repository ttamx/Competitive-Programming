#include "celeb.cpp"
#include <cstdio>

static int N;
static int K;
static std::vector<long long> X;
static std::vector<int> M;

int main()
{
  scanf("%d %d", &N, &K);

  for(int i=0; i<N; i++) {
    long long xx;
    scanf("%lld", &xx);
    X.push_back(xx);
  }

  for(int j=0; j<K; j++) {
    long long mm;
    scanf("%lld", &mm);
    M.push_back(mm);
  }

  auto rev = max_revenue(N, K,
			 X, M);
  
  for(int j=0; j<K; j++) {
    printf("%lld ", rev[j]);
  }
  printf("\n");
  
  return 0;
}
