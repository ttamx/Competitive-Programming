#include "orgdelivery.cpp"
#include <vector>
#include <cstdio>

using namespace std;

int main()
{
  int dummy;
  int N, Q;
  vector<int> P;
  vector<long long> V;
  vector<int> W;
  vector<int> A;
  vector<int> B;

  dummy = scanf("%d %d",&N,&Q);
  for(int i=0; i<N; i++) {
    int p,w;
    long long v;
    dummy = scanf("%d %lld %d",&p,&v,&w);
    P.push_back(p);
    V.push_back(v);
    W.push_back(w);
  }
  for(int j=0; j<Q; j++) {
    int a,b;
    dummy = scanf("%d %d",&a,&b);
    A.push_back(a);
    B.push_back(b);
  }
  vector<long long> res = mincost(N, P, V, W,
				  Q, A, B);
  for(int j=0; j<Q; j++) {
    printf("%lld\n", res[j]);
  }
}
