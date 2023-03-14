
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define inbuf_len 1 << 16
#define outbuf_len 1 << 16

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E);

int main() {
  int tmp;

  /* Set input and output buffering */
  char *inbuf, *outbuf;
  inbuf = (char*) malloc(inbuf_len * sizeof(char));
  outbuf = (char*) malloc(outbuf_len * sizeof(char));
  tmp = setvbuf(stdin, inbuf, _IOFBF, inbuf_len);
  assert(tmp == 0);
  tmp = setvbuf(stdout, outbuf, _IOFBF, outbuf_len);
  assert(tmp == 0);

  int N, C, R;
  int *K, *S, *E;
  tmp = scanf("%d %d %d", &N, &C, &R);
  assert(tmp == 3);
  K = (int*) malloc((N-1) * sizeof(int));
  S = (int*) malloc(C * sizeof(int));
  E = (int*) malloc(C * sizeof(int));
  int i;
  for (i = 0; i < N-1; i++) {
    tmp = scanf("%d", &K[i]);
    assert(tmp == 1);
  }
  for (i = 0; i < C; i++) {
    tmp = scanf("%d %d", &S[i], &E[i]);
    assert(tmp == 2);
  }

  printf("%d\n", GetBestPosition(N, C, R, K, S, E));

  return 0;

}
