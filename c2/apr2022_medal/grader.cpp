#include<stdio.h>
#include "medal.cpp"
#include<vector>
#include<utility>
#include<assert.h>
int main()
{
    int N,Q,V,S,T;
    assert(scanf("%d %d",&N,&Q)==2);
    std::vector<int>W;
    for(int i = 0;i < N;i++)
    {
        assert(scanf("%d",&V)==1);
        W.emplace_back(V);
    }
    std::vector<std::pair<int,int> >R;
    for(int i = 0;i < N-1;i++)
    {
        assert(scanf("%d %d",&S,&T)==2);
        R.emplace_back(std::make_pair(S,T));
    }
    std::vector<std::vector<int> >P;
    for(int i = 0;i < Q;i++)
    {
        std::vector<int>Path;
        int A,B,X;
        assert(scanf("%d %d %d",&A,&B,&X)==3);
        Path.emplace_back(A);
        Path.emplace_back(B);
        Path.emplace_back(X);
        P.emplace_back(Path);
    }
    initialize(N,Q,W,R);
    for(int i = 0;i < Q;i++)
    {
        printf("%lld\n",query(P[i][0],P[i][1],P[i][2]));
    }
	return 0;
}
