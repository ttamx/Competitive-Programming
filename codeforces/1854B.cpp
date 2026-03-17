#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
int a[N];
bitset<N> dp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    dp[a[0]]=1;
    ll ans=a[0];
    ll cur=a[0];
    for(int i=1;i<n;i++){
        if(cur<i)break;
        cur+=a[i];
        dp|=(dp>>i)<<(a[i]+i);
    }
    ll sum=0;
    for(int i=0;i<N;i++){
        sum+=a[i];
        if(dp[i]){
            ans=max(ans,sum-i);
        }
    }
    cout << ans << "\n";
}