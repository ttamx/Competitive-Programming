#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n+1),mn(n+2);
    for(int i=1;i<=n;i++)cin >> a[i],a[i]+=a[i-1];
    mn[n+1]=1e18;
    for(int i=n;i>=1;i--)mn[i]=min(mn[i+1],a[i]);
    ll mx=-1e18,ans=0;
    for(int i=0;i<=n;i++){
        ll res=max(0ll,a[i]-mn[i+1]);
        if(res>mx)mx=res,ans=a[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}