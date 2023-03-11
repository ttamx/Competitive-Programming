#include <stdio.h>
#include <vector>
#include <utility>
#include "panda.h"
static int type[100005],P[100005],L[100005],X[100005],A[100005],B[100005];
int main()
{
    int N,M,S,Q;
    scanf("%d %d %d %d",&N,&M,&S,&Q);
    std::vector<std::vector<int> >R;
    std::vector<int>tmp(2);
    for(int i = 0;i < M;i++)
    {
        scanf("%d %d",&tmp[0],&tmp[1]);
        R.push_back(tmp);
    }
    for(int i = 0;i < Q;i++)
    {
        scanf("%d",&type[i]);
        if(type[i]==1)
        {
            scanf("%d %d %d",&P[i],&L[i],&X[i]);
        }
        else if(type[i]==2)
        {
            scanf("%d %d %d",&P[i],&L[i],&X[i]);
        }
        else if(type[i]==3)
        {
            scanf("%d %d",&A[i],&B[i]);
        }
    }
    initialize(N,M,S,R);
    for(int i = 0;i < Q;i++)
    {
        if(type[i]==1)
        {
            panda_spawn(P[i],L[i],X[i]);
        }
        else if(type[i]==2)
        {
            panda_evac(P[i],L[i],X[i]);
        }
        else if(type[i]==3)
        {
            printf("%d\n",travel(A[i],B[i]));
        }
    }
    return 0;
}
