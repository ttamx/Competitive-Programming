#include "encoder.h"
#include "encoderlib.h"

void encode(int N, int M[])
{
  int i;
  for(i=0; i<N; i++)
    send(M[i]);
}
