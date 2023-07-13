#include<bits/stdc++.h>

using namespace std;

const int N=105;
const int K=1e5+5;

int n,k;
int a[N],dp[K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=k;i++){
        for(int j=1;j<=n;j++){
            if(i<a[j])break;
            dp[i]|=dp[i-a[j]]^1;
        }
    }
    cout << (dp[k]?"First":"Second");
}