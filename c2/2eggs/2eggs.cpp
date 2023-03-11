#include "2eggs.h"
#include<bits/stdc++.h>

using namespace std;

int height_threshold(int N, int Q) {
  int q=Q;
  int cant=N;
  bool boom=false;
  int idx=0;
  while(!boom&&idx<cant-1){
    boom=drop_egg(1,min(idx+q,N-1));
    if(!boom)idx=min(idx+q,N-1);
    else cant=min(idx+q,N-1);
    --q;
  }
  if(idx==cant-1)return cant;
  while(q&&idx<cant-1){
    boom=drop_egg(2,++idx);
    if(boom)return idx;
    --q;
  }
  return min(++idx,N);
}