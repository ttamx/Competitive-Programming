#include "factories.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX_N          500000
#define MAX_Q          100000
#define MAX_SUM_ST    1000000
#define MAX_VALUE  1000000000

static int N, Q;
static int A[MAX_N], B[MAX_N], D[MAX_N];
static int S[MAX_N];
static int T[MAX_N];
static int X[MAX_SUM_ST];
static int Y[MAX_SUM_ST];

static int Qx[MAX_N];
static int Qy[MAX_N];

int main() {
  int i, j, k;
  int STop, TTop;

  if (2 != scanf("%d%d", &N, &Q)) {
    fprintf(stderr, "error: cannot read N and Q.\n");
    exit(1);
  }
  if (!(2 <= N && N <= MAX_N)) {
    fprintf(stderr, "error: N is out of bounds.\n");
    exit(1);
  }
  if (!(1 <= Q && Q <= MAX_Q)) {
    fprintf(stderr, "error: Q is out of bounds.\n");
    exit(1);
  }
  for (i = 0; i < N - 1; ++i) {
    if (1 != scanf("%d", &A[i])) {
      fprintf(stderr, "error: cannot read A[%d].\n", i);
      exit(1);
    }
    if (!(0 <= A[i] && A[i] <= N - 1)) {
      fprintf(stderr, "error: A[%d] is out of bounds.\n", i);
      exit(1);
    }
    if (1 != scanf("%d", &B[i])) {
      fprintf(stderr, "error: cannot read B[%d].\n", i);
      exit(1);
    }
    if (!(0 <= B[i] && B[i] <= N - 1)) {
      fprintf(stderr, "error: B[%d] is out of bounds.\n", i);
      exit(1);
    }
    if (A[i] == B[i]) {
      fprintf(stderr, "error: B[%d] is equal to A[%d].\n", i, i);
      exit(1);
    }
    if (1 != scanf("%d", &D[i])) {
      fprintf(stderr, "error: cannot read D[%d].\n", i);
      exit(1);
    }
    if (!(1 <= D[i] && D[i] <= MAX_VALUE)) {
      fprintf(stderr, "error: D[%d] is out of bounds.\n", i);
      exit(1);
    }
  }

  STop = 0;
  TTop = 0;

  for (j = 0; j < Q; ++j) {
    if (2 != scanf("%d%d", &S[j], &T[j])) {
      fprintf(stderr, "error: cannot read L[%d] and R[%d].\n", j, j);
      exit(1);
    }

    if(STop + S[j] > MAX_SUM_ST) {
      fprintf(stderr, "error: S[0] + S[1] + ... + S[%d] is out of bounds.\n", j);
      exit(1);
    }

    if(TTop + T[j] > MAX_SUM_ST) {
      fprintf(stderr, "error: T[0] + T[1] + ... + T[%d] is out of bounds.\n", j);
      exit(1);
    }

    for (k = 0; k < S[j]; ++k, ++STop) {
      if (1 != scanf("%d", &X[STop])) {
        fprintf(stderr, "error: cannot read X[%d][%d].\n", j, k);
        exit(1);
      }

      if (!(0 <= X[STop] && X[STop] <= N - 1)) {
        fprintf(stderr, "error: cannot read X[%d][%d].\n", j, k);
        exit(1);
      }
    }

    for (k = 0; k < T[j]; ++k, ++TTop) {
      if (1 != scanf("%d", &Y[TTop])) {
        fprintf(stderr, "error: cannot read Y[%d][%d].\n", j, k);
        exit(1);
      }

      if (!(0 <= Y[TTop] && Y[TTop] <= N - 1)) {
        fprintf(stderr, "error: cannot read Y[%d][%d].\n", j, k);
        exit(1);
      }
    }
  }
  
  STop = 0;
  TTop = 0;
  Init(N, A, B, D);

  for (j = 0; j < Q; ++j) {
    for (k = 0; k < S[j]; k++) {
        Qx[k] = X[STop++];
    }
    for (k = 0; k < T[j]; k++) {
        Qy[k] = Y[TTop++];
    }

    printf("%lld\n", Query(S[j], Qx, T[j], Qy));
  }


  return 0;
}
