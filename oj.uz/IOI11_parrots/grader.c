#include "encoder.h"
#include "decoder.h"
#include "encoderlib.h"
#include "decoderlib.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_N  1000
#define MAX_L 10000

#define CHANNEL_RANGE 65535
#define MAX_EXPANSION 10

static int message[MAX_N];
static int N; // NN;
static int encoded_message[MAX_L];
static int L;
static int output_message[MAX_N];
static int O;

inline
void my_assert(int e){ if (!e) abort(); };

void send(int a)
{
  if(L == MAX_L) {
    printf("Encoded message too long.\n");
    exit(0);
  }
  encoded_message[L] = a;
  L++;
}

void output(int b)
{
  if(O == N)
    O++;
  if(O > N)
    return;
  output_message[O] = b;
  O++;
}

static void shuffle()
{
  int t,i;
  i=0;
  while(i < L-1) {
    t = encoded_message[i];
    encoded_message[i] = encoded_message[i+1];
    encoded_message[i+1] = t;
    i += 2;
  }
}

static void check_encoded_message()
{
  int i;
  if(L > MAX_EXPANSION * N) {
    printf("Encoded message too long.");
    exit(0);
  }
  for(i=0; i < L; i++)
    if((encoded_message[i] < 0) || 
       (encoded_message[i] > CHANNEL_RANGE)) {
      printf("Bad encoded integer.\n");
      exit(0);
    }
}

static int check_output()
{
  int i;

  if(O!=N)
    return 0;
  for(i = 0; i < N; i++)
    if(message[i] != output_message[i])
      return 0;
  return 1;
}

int main()
{
  int i,t;
  double ratio;

  my_assert(1==scanf("%d",&N));
  for(i = 0; i < N; i++)
    my_assert(1==scanf("%d",&message[i]));

  ratio = 0;

  for(t=0; t<2; t++) {
    L = 0;
    encode(N,message);

    check_encoded_message();

    if((double) L / N > ratio)
      ratio = ((double)L)/N;
    
    if(t==1)
      shuffle();
  
    // NN = 0;
    O = 0;
    decode(N,L,encoded_message);

    if(!check_output()) {
      printf("Incorrect.\n");
      exit(0);
    }
  }
  printf("Correct.\n");
  fprintf(stderr,"Ratio = %3.3f\n",ratio);

  return 0;
}
