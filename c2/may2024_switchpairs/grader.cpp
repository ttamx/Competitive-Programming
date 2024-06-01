#include "switchpairs.cpp"
#include <vector>
#include <cstdio>
#include <cstdlib>

static const int MAX_N = 2000;
static const int MAX_Q = 15000;

static int qcount;
static int nn;
static int A[MAX_N];
static int B[MAX_N];
static int X[MAX_N];
static int Y[MAX_N];

int control_switches(std::vector<int> V)
{
  qcount++;
  if(qcount > MAX_Q) {
    printf("ERROR: too many calls to control_switches\n");
    exit(0);
  }

  if(V.size() != 2*nn) {
    for(auto x:V)cerr << x << " ";
    cerr << "\n";
    printf("ERROR: incorrect parameter V\n");
    exit(0);
  }

  for(int i=0; i<nn; i++) {
    if((V[A[i]] != X[i]) || (V[B[i]] != Y[i]))
      return i;
  }
  printf("Correct\n%d calls\n", qcount);
  exit(0);
}

int main()
{
  scanf("%d",&nn);
  for(int i=0; i<nn; i++)
    scanf("%d %d %d %d",&A[i],&B[i],&X[i],&Y[i]);

  qcount = 0;
  solve(nn);
  printf("ERROR: solve failed to open every door\n");
}
