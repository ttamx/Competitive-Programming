#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N=1e5+5;
const ll mod=1e9+7;

ll n,q;
ll h[N],pos[N];
ll pw2[N];
ll ans=0;

struct fenwick{
    ll t[N];
    void add(ll i,ll v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(ll i){
        ll res=0;
        while(i)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    pw2[0]=1;
    for(ll i=1;i<N;i++){
        pw2[i]=(pw2[i-1]*2)%mod;
    }
    cin >> n >> q;
    vector<pair<ll,ll>> in;
    for(ll i=1;i<=n;i++){
        cin >> h[i];
    }
    assert(q==1);
    ll a,b;
    cin >> a >> b;
    h[a]=b;
    for(int i=1;i<=n;i++){
        in.push_back({h[i],i});
    }
    sort(in.begin(),in.end());
    for(int i=0;i<n;i++)pos[in[i].second]=i;
    for(ll i=1;i<=n;i++){
        ll l=pos[i],r=n-pos[i]-1;
        ans=(ans+h[i]*pw2[l])%mod;
        ans=(ans+mod-((h[i]*pw2[r])%mod))%mod;
    }
    cout << ans;
}