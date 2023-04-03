#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

ll n,k;
ll c[32];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> c[0];
    for(int i=1;i<32;i++)c[i]=1e18;
    for(int i=0;i<k;i++){
        int x;
        ll y;
        cin >> x >> y;
        c[x]=min(c[x],y);
    }
    for(int i=1;i<32;i++)c[i]=min(c[i],2ll*c[i-1]);
    ll ans=0;
    for(int i=31;i>=0;i--){
        if(n>=(1ll<<i)){
            n-=(1ll<<i);
            ans+=c[i];
        }
    }
    cout << ans;
}