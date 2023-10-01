#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

long long mod=1e9+7;

const int N=1e6+5;

int n,k,d;
int a[N];
ll dp[N],pl[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> d;
    for(int i=1;i<=k;i++)cin >> a[i];
    sort(a+1,a+k+1);
    dp[0]=1;
    for(int i=1;i<=k;i++){
        assert(a[i]!=a[i-1]);
        pl[i]+=pl[i-1];
        pl[i]%=mod;
        dp[i]=dp[i-1]+pl[i];
        dp[i]%=mod;
        int l=lower_bound(a+1,a+k+1,a[i]+2)-a;
        int r=upper_bound(a+1,a+k+1,a[i]+d)-a;
        pl[l]+=dp[i];
        pl[l]%=mod;
        pl[r]+=mod-dp[i];
        pl[r]%=mod;
    }
    cout << dp[k];
}