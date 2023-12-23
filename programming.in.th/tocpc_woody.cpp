#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const int M=505;
const ll inf=1e18;

int n,x,y;
ll dp[M][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x >> y;
    for(int i=0;i<=x;i++)for(int j=0;j<=y;j++)dp[i][j]=inf;
    dp[0][0]=0;
    for(int t=1;t<=n;t++){
        int xi,yi,c;
        cin >> xi >> yi >> c;
        auto tmp=dp;
        for(int i=x;i>=0;i--){
            for(int j=y;j>=0;j--){
                auto &res=dp[min(i+xi,x)][min(j+yi,y)];
                res=min(res,tmp[i][j]+c);
            }
        }
    }
    cout << (dp[x][y]==inf?-1:dp[x][y]);
}