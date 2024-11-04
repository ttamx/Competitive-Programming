#include "train.cpp"
#include <vector>
#include <cstdio>

using namespace std;

static int N,M;
static vector<int> s;
static vector<int> t;
static vector<int> c;

int main()
{
  scanf("%d %d",&N,&M);

  for(int i=0; i<M; i++) {
    int ss, tt, cc;
    scanf("%d %d %d",&ss,&tt,&cc);
    s.push_back(ss);
    t.push_back(tt);
    c.push_back(cc);
  }

  int result = find_min_cost(N,M,
			     s, t, c);

  printf("%d\n",result);
  return 0;
}
