#include <cstdio>
#include <vector>
#include "fatigue.cpp"
int main() {
    int N,M;
    scanf("%d %d",&N,&M);
    std::vector<int> A(N), W(N);
    for(int i = 0;i < N;i++) {
        scanf("%d",&A[i]);
    }
    for(int i = 0;i < N;i++) {
        scanf("%d",&W[i]);
    }
    initialize(N,A,W);
    std::vector<long long> Answer;
    for(int i = 0;i < M;i++) {
        int e;
        scanf("%d",&e);
        if(e==1) {
            int X,V;
            scanf("%d %d",&X,&V);
            change_weight(X,V);
        } else if(e==2) {
            int p;
            scanf("%d",&p);
            std::vector<int> B(p);
            for(int j = 0;j < p;j++) {
                scanf("%d",&B[j]);
            }
            Answer.push_back(point_fatigue(B));
        } else {
            int q;
            scanf("%d",&q);
            std::vector<std::vector<int>> In(q,std::vector<int>(2));
            for(int j = 0;j < q;j++) {
                scanf("%d %d",&In[j][0],&In[j][1]);
            }
            Answer.push_back(interval_fatigue(In));
        }
    }
    for(int i = 0;i < Answer.size();i++){
        printf("%lld\n",Answer[i]);
    }
}