#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,w;
    cin >> n >> w;
    int s=0;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
        s+=b[i];
    }
    vector<int> dp(s+1,w+1);
    dp[0]=0;
    for(int i=0;i<n;i++){
        for(int j=s;j>=b[i];j--){
            dp[j]=min(dp[j],dp[j-b[i]]+a[i]);
        }
    }
    for(int i=s;i>=0;i--){
        if(dp[i]<=w){
            cout << i << "\n";
            exit(0);
        }
    }
    assert(false);
}