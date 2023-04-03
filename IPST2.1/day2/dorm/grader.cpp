#include <stdio.h>
#include <vector>
#include "dorm.h"
#include "dorm.cpp"
using namespace std;
int main(){
	int N,M,Q;
    scanf("%d %d %d",&N,&M,&Q);
    std::vector<std::vector<int> > Req(M,std::vector<int> (2,0));
    for(int i = 0;i < M;i++){
        scanf("%d %d",&Req[i][0],&Req[i][1]);
    }
    int P[Q];
    for(int i = 0;i < Q;i++){
        scanf("%d",&P[i]);
    }
    init(N,Req);
    for(int i = 0;i < Q;i++){
        printf("%lld\n",least_crowded(P[i]));
    }
}
