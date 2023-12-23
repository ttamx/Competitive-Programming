#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const ll mod=1e9+7;
const ll inv2=5e8+4;

int n;
ll h[N],w[N];
ll ans,sum;
stack<pair<ll,ll>> st;

ll calc(ll x){
    x%=mod;
    return x*(x+1)%mod*inv2%mod;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> h[i];
    for(int i=1;i<=n;i++)cin >> w[i];
    for(int i=1;i<=n;i++){
        ans+=calc(w[i])*calc(h[i])%mod;
        ans%=mod;
        ll cnt=0;
        while(!st.empty()&&st.top().first>h[i]){
            auto [x,y]=st.top();
            st.pop();
            cnt+=y;
            cnt%=mod;
            sum+=mod-calc(x)*y%mod;
            sum%=mod;
        }
        ans+=w[i]*(sum+calc(h[i])*cnt%mod)%mod;
        ans%=mod;
        cnt+=w[i];
        st.emplace(h[i],cnt);
        sum+=calc(h[i])*cnt%mod;
        sum%=mod;
    }
    cout << ans;
}