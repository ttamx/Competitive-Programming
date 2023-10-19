#include<stdio.h>
#include "tnt.h"
#include<vector>
#include<algorithm>
#include <assert.h>
static int times,A,B,N,Q;

bool find_tnt(std::vector<int>city)
{
    std::sort(city.begin(),city.end());
    for(int i = 0;i < city.size();i++)
    {
        if(city[i]<0 || city[i]>=N)
        {
            printf("City out of range\n");
            exit(-1);
        }
        if(i>0 && city[i]==city[i-1])
        {
            printf("Duplicate city\n");
            exit(-1);
        }
    }
    if(times==Q)
    {
        printf("Asked more than %d queries\n",Q);
        exit(-1);
    }
    times++;
    bool find=false;
    for(int i = 0;i < city.size();i++)
      if((A + B*times)%N==city[i])find=true;
    return find;
}

int main()
{
  times=0;
  assert(scanf("%d %d %d %d",&N,&Q,&A,&B)==4);
  std::vector<int>sol=find_truck(N);
    if(sol[0]==A && sol[1]==B)
      printf("Pass\n");
    else {
      printf("Expected A = %d,B = %d\nOutput A = %d,B = %d\n",A,B,sol[0],sol[1]);
      return 0;
    }
  return 0;
}
