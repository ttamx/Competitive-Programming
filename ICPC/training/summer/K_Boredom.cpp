#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

using ll = long long;

ll a[N];
ll dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x]+=x;
    }
    dp[1]=a[1];
    for(int i=2;i<N;i++){
        dp[i]=max(dp[i-1],dp[i-2]+a[i]);
    }
    cout << dp[N-1] << "\n";
}