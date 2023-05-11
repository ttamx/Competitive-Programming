#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5005;

int q;
ll dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++){
        for(int j=0;j<N;j++){
            dp[i][j]=dp[i-1][j]
        }
    }
    cin >> q;
}