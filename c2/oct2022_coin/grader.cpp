#include "coin.cpp"
#include <stdio.h>
#include <vector>
int main()
{
	int N,Q,L;
    scanf("%d %d %d",&N,&Q,&L);
    std::vector<int>Rail(N);
    for(int i = 0;i < N;i++)
    {
        scanf("%d",&Rail[i]);
    }
    std::vector<std::vector<int> >Coins(Q,std::vector<int>(3,0));
    for(int i = 0;i < Q;i++)
    {
        scanf("%d %d %d",&Coins[i][0],&Coins[i][1],&Coins[i][2]);
    }
    initialize(N,Rail,L);
	std::vector<int>ans(Q);
	ans = max_dist(Coins);
    for(int i = 0;i < Q;i++)
    {
        printf("%d\n",ans[i]);
    }
}
