#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=165;
const int T=85;

int n,l,t;
int dp[T][T][T];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> l >> n >> t;
    t/=2;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        int d1=x+y-2;
        int d2=x-1+l-y;
        int d3=y-1+l-x;
        int d4=2*l-x-y;
        for(int i1=t;i1>=0;i1--){    
            for(int i2=t;i2>=0;i2--){
                for(int i3=t;i3>=0;i3--){
                    dp[i1][i2][i3]+=d4;
                    if(i1>=d1){
                        dp[i1][i2][i3]=min(dp[i1][i2][i3],dp[i1-d1][i2][i3]);
                    }
                    if(i2>=d2){
                        dp[i1][i2][i3]=min(dp[i1][i2][i3],dp[i1][i2-d2][i3]);
                    }
                    if(i3>=d3){
                        dp[i1][i2][i3]=min(dp[i1][i2][i3],dp[i1][i2][i3-d3]);
                    }
                }
            }
        }
    }
    cout << (dp[t][t][t]<=t?"Yes":"No");
}