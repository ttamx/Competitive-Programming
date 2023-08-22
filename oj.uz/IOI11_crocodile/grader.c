#include "crocodile.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50000
#define MAX_M 10000000

static int N, M;
static int R[MAX_M][2];
static int L[MAX_M];
static int K;
static int P[MAX_N];
static int solution;

inline 
void my_assert(int e) {if (!e) abort();}

void read_input()
{
  int i;
  my_assert(3==scanf("%d %d %d",&N,&M,&K));
  for(i=0; i<M; i++)
    my_assert(3==scanf("%d %d %d",&R[i][0],&R[i][1],&L[i]));
  for(i=0; i<K; i++)
    my_assert(1==scanf("%d",&P[i]));
  my_assert(1==scanf("%d",&solution));
}

int main()
{
  int ans;
  read_input();
  ans = travel_plan(N,M,R,L,K,P);
  if(ans==solution)
    printf("Correct.\n");
  else
    printf("Incorrect. Returned %d, Expected %d.\n",ans,solution);

  return 0;
}
