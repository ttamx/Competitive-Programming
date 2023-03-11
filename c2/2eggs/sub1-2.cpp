#include "2eggs.h"

int height_threshold(int N, int Q) {
  bool can=drop_egg(1,1);
  if(can)return 1;
  return 2;
}