#include "2eggs.h"

int height_threshold(int N, int Q) {
  bool boom=drop_egg(1,2);
  if(boom){
    boom=drop_egg(2,1);
    if(boom)return 1;
    else return 2;
  }else{
    boom=drop_egg(1,3);
    if(boom)return 3;
    else return 4;
  }
}