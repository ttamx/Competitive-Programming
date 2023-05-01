#include<cstdio>
#include<vector>
#include "bestbank.cpp"
using namespace std;

struct Cmd {
  bool ask;
  int a,b;
  long long c;
  Cmd(int a,int b,long long c):a(a),b(b),c(c),ask(false){}
  Cmd(int a,int b):a(a),b(b),ask(true){}
};

int main()
{
	int N,K,Q;
    scanf("%d %d %d",&N,&K,&Q);
    vector<vector<int>>R;
    vector<vector<long long>>B;
    for(int i = 0;i < N-1;i++)
    {
        vector<int>tmp;
        int R0,R1,R2;
        scanf("%d %d %d",&R0,&R1,&R2);
        tmp.emplace_back(R0);
        tmp.emplace_back(R1);
        tmp.emplace_back(R2);
        R.emplace_back(tmp);
    }
    for(int i = 0;i < K;i++)
    {
        vector<long long>tmp;
        long long B0,B1,B2;
        scanf("%lld %lld %lld",&B0,&B1,&B2);
        tmp.emplace_back(B0);
        tmp.emplace_back(B1);
        tmp.emplace_back(B2);
        B.emplace_back(tmp);
    }
    int m,P,F,S,Y;
    long long L;
    vector<Cmd> stm;
    for(int i = 0;i < Q;i++)
    {
        scanf("%d",&m);
        if(m==1)
        {
            scanf("%d %d %lld",&P,&F,&L);
            // update_bank(P,F,L);
            stm.emplace_back(P,F,L);
        }
        else if(m==2)
        {
            scanf("%d %d",&S,&Y);
            // printf("%lld\n",find_best_bank(S,Y));
            stm.emplace_back(S,Y);
        }
    }
    initialize(N,Q,R,B);
    for(int i=0;i<stm.size();i++)
    {
      if(stm[i].ask) {
        printf("%lld\n",find_best_bank(stm[i].a,stm[i].b));
      }
      else {
        update_bank(stm[i].a,stm[i].b,stm[i].c);
      }
    }

}
