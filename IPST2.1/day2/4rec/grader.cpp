#include <stdio.h>
#include <vector>
#include <assert.h>
#include "4rec.h"
#include "4rec_sub5.cpp"
int main(){
    int N,P,Q;
    scanf("%d %d %d",&N,&P,&Q);
    std::vector<std::vector<int> > Point(N,std::vector<int> (2,0));
    for(int i = 0;i < N;i++){
        scanf("%d %d",&Point[i][0],&Point[i][1]);
    }
    printf("%lld",find_rec(Point,P,Q));
}
