#include<bits/stdc++.h>

using namespace std;

const int N=1121;
const int K=15;

bool sieve[N];
vector<int> prime;

int dp[K][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(sieve[i])continue;
        prime.emplace_back(i);
        for(int j=i+i;j<N;j+=i)sieve[j]=true;
    }
    dp[0][0]=1;
    for(auto x:prime){
        for(int j=N-1;j>=x;j--){
            for(int i=1;i<K;i++){
                dp[i][j]+=dp[i-1][j-x];
            }
        }
    }
    int n,k;
    while(cin >> n >> k){
        if(n==0&&k==0)break;
        cout << dp[k][n] << '\n';
    }
}