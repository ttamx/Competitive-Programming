#include "decoder.h"
#include "decoderlib.h"

void decode(int N, int L, int X[])
{
  int i, b;
  for(i=0; i<L; i++) {
    b = X[i];
    output(b);
  }
}
