#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,q;
int a[N],dp[N],dp2[N],dp3[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=2;i<=n;i++){
        dp[i]=dp[i-1]+(a[i-2]>=a[i-1]&&a[i-1]>=a[i]);
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << (l==r?1:r-l+1-(dp[r]-dp[l+1])) << "\n";
    }
}