#include "rescue.cpp"
#include <cstdio>

static std::vector<int> X;
static std::vector<int> Y;
static int NN,Q;

int main()
{
  int tmp;

  tmp = scanf("%d %d", &NN, &Q);
  for(int i=0; i<NN; i++) {
    int x,y;
    tmp = scanf("%d %d",&x,&y);
    X.push_back(x);
    Y.push_back(y);
  }
  init_rescue(NN,Q,X,Y);

  for(int i=0; i<Q; i++) {
    int k,r;
    tmp = scanf("%d",&k);
    if(k==1) {
      int a,b,c,d;
      tmp = scanf("%d %d %d %d",&a,&b,&c,&d);
      printf("%d\n", answer_query(a,b,c,d));
    } else {
      tmp = scanf("%d",&r);
      cancel_request(r);
    }
  }
}
