#include "cheat.cpp"
#include <cstdio>

static int NN, Q;

int main()
{
  char buf[10];
  
  scanf("%d %d",&NN,&Q);
  for(int i=0; i<NN+Q; i++) {
    int p1,p2;
    scanf("%s %d %d",buf,&p1,&p2);
    if(buf[0] == 'C')
      cheat(p1,p2);
    else
      printf("%d\n",investigate(p1,p2));
  }
}

