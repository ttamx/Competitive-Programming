#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;
const int inf=1e9;

int n;
int dp[N];
int lz;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=2;i<=n;i++)dp[i]=inf;
    for(int i=1;i<=n;i++){
        int t;
        cin >> t;
        if(t==1){
            int x;
            cin >> x;
            lz++;
            dp[x]=-lz;
        }else{
            int x,y;
            cin >> x >> y;
            dp[y]=min(dp[y],dp[x]);
            dp[x]++;
        }
    }
    for(int i=1;i<=n;i++)dp[i]+=lz;
    for(int i=1;i<=n;i++)cout << (dp[i]<=n?dp[i]:-1) << " ";
}