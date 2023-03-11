#include <stdio.h>
#include "pattern.cpp"
#include <vector>
int main()
{
    int N,M,P;
    scanf("%d %d %d",&N,&M,&P);
    std::vector<std::vector<int> >Path(N-1,std::vector<int>(2,0));
    for(int i = 0;i < N-1;i++)
    {
        scanf("%d %d",&Path[i][0],&Path[i][1]);
    }
    std::vector<std::vector<int> >p(P,std::vector<int>(2,0));
    for(int i = 0;i < P;i++)
    {
        scanf("%d %d",&p[i][0],&p[i][1]);
    }
    printf("%d",total_pattern(N,M,Path,p));
}
