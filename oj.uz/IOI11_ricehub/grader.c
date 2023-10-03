#include "ricehub.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_R  1000000

static int R, L;
static long long B;
static int X[MAX_R];
static int solution;

inline 
void my_assert(int e) {if (!e) abort();}

static void read_input()
{
  int i;
  my_assert(3==scanf("%d %d %lld",&R,&L,&B));
  for(i=0; i<R; i++)
    my_assert(1==scanf("%d",&X[i]));
  my_assert(1==scanf("%d",&solution));
}

int main()
{
  int ans;
  read_input();
  ans = besthub(R,L,X,B);
  if(ans==solution)
    printf("Correct.\n");
  else
    printf("Incorrect.  Returned %d instead of %d.\n",ans,solution);

  return 0;
}
