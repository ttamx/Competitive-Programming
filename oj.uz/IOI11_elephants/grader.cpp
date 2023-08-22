#include "elephants.cpp"
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000
#define MAX_M 1000000

static int NN,LL,M;
static int XX[MAX_N];
static int ii[MAX_M];
static int yy[MAX_M];
static int sol[MAX_M];

inline 
void my_assert(int e) {if (!e) abort();}

void read_input()
{
  int i;
  my_assert(3==scanf("%d %d %d",&NN,&LL,&M));
  for(i=0; i<NN; i++)
    my_assert(1==scanf("%d",&XX[i]));
  for(i=0; i<M; i++)
    my_assert(3==scanf("%d %d %d",&ii[i],&yy[i],&sol[i]));
}

int main()
{
  int i, ans;

  read_input();
  init(NN,LL,XX);
  for(i=0; i<M; i++) {
    ans = update(ii[i],yy[i]);
    if(ans==sol[i])continue;
      printf("Incorrect.  In %d-th move, answered %d (%d expected).\n",
	     i+1, ans, sol[i]);
    return 0;
  }
  printf("Correct.\n");
  return 0;
}
