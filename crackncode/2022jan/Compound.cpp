#include<bits/stdc++.h>

using namespace std;

bool sieve[1005];
int dp[100]
vector<int> prime;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<=1000;i++){
        if(sieve[i])continue;
        prime.push_back(i);
        for(int j=i+i;j<=1000;j+=i)sieve[j]=true;
    }
}