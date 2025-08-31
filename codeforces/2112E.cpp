#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int INF=INT_MAX/2;

int dp[N],aux[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<N;i++)dp[i]=aux[i]=INF;
    dp[1]=1;
    for(int i=1;i<N;i++){
        dp[i]=min(dp[i],aux[i]+1);
        if(i+2<N)aux[i+2]=min(aux[i+2],dp[i]);
        for(int j=1;(i+2)*j<N;j++){
            int p=(i+2)*j;
            aux[p]=min(aux[p],aux[j]+aux[i+2]);
        }
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        cout << (dp[n]<INF?dp[n]:-1) << "\n";
    }
}