#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const int M=2*N;
const int MOD=1e9+7;
const int INV=5e8+4;

int n;
ll a[N][2];
ll ans;
ll pre[N],suf[N],v[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)cin >> a[i][0];
    for(int i=0;i<n;i++)cin >> a[i][1];
    for(int mask=0;mask<1<<n;mask++){
        for(int i=0;i<n;i++)v[i]=pre[i]=suf[i]=a[i][mask>>i&1];
        for(int i=1;i<n;i++)pre[i]=max(pre[i],pre[i-1]);
        for(int i=n-2;i>=0;i--)suf[i]=max(suf[i],suf[i+1]);
        for(int i=1;i<n-1;i++)ans=(ans+min(pre[i],suf[i])-v[i])%MOD;
    }
    cout << ans;
}