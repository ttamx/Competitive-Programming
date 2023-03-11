#include "die.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1001;

string dp[N];

bool ok=false;

string A(int T, int C){
    if(ok)return dp[C];
    ok=true;
    for(int i=1;i<=14;i++)dp[i]=dp[i-1]+"+";
    for(int i=15;i<N;i++){
        dp[i]=dp[i-1]+"+";
        for(int j=2;j<=14;j++)if(i%j==0&&dp[j].size()+dp[i/j].size()+6<dp[i].size())dp[i]=dp[i/j]+"[>"+dp[j]+"<-]>";
        for(int j=i-1;j>0;j--)if(dp[j+1].size()+1<dp[j].size())dp[j]=dp[j+1]+"-";else break;
    }
    return dp[C];
}
