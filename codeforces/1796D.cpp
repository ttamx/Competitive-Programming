#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    ll n,k,x;
    cin >> n >> k >> x;
    vector<ll> a(n+1),qs(n+1);
    for(ll i=1;i<=n;i++){
        cin >> a[i];
        a[i]-=x;
        qs[i]=qs[i-1]+a[i];
    }
    ll ans=0;
    x*=2;
    if(k==n){
        for(int i=1;i<=n;i++){
            a[i]+=x;
            qs[i]=qs[i-1]+a[i];
        }
        ll mn=0;
        for(int i=1;i<=n;i++){
            ans=max(ans,qs[i]-mn);
            mn=min(mn,qs[i]);
        }
    }else if(x>=0){
        vector<ll> sub(k+1,-1e18);
        ll mn=1e18;
        for(ll i=1;i<=n;i++){
            for(ll j=0;j<=k&&i-j>=0;j++){
                sub[j]=max(sub[j],qs[i]-qs[i-j]);
            }
            if(i>=k){
                mn=min(mn,qs[i-k]);
                ans=max(ans,qs[i]-mn+(k*x));
            }
        }
        for(ll i=0;i<=k;i++)ans=max(ans,sub[i]+(x*i));
    }else{
        vector<ll> sub(k+1,-1e18);
        multiset<pair<ll,ll>> ms;
        ms.emplace(qs[0],0);
        for(ll i=1;i<=n;i++){
            for(ll j=0;j<=k&&i-(n-j)>=0;j++){
                sub[j]=max(sub[j],qs[i]-qs[i-(n-j)]);
            }
            while(!ms.empty()&&ms.begin()->second<i-(n-k))ms.erase(ms.begin());
            ans=max(ans,qs[i]-ms.begin()->first);
            ms.emplace(qs[i],i);
        }
        for(ll i=0;i<=k;i++)ans=max(ans,sub[i]+(x*(k-i)));
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}