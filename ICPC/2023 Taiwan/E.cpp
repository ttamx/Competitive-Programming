#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using P = pair<ll,ll>;

const ll INF = LLONG_MAX/2;

void runcase(){
    int n;
    ll pad;
    cin >> n >> pad;
    vector<pair<P,P>> a(n);
    ll mnx=INF,mny=INF,mxx=-INF,mxy=-INF;
    for(auto &[u,v]:a){
        cin >> u.first >> u.second >> v.first >> v.second;
        mnx=min(mnx,u.first);
        mny=min(mny,u.second);
        mxx=max(mxx,v.first);
        mxy=max(mxy,v.second);
    }
    map<ll,pair<ll,ll>> dat;
    dat[INF]={-INF,mnx-pad};
    ll ans=mnx;
    sort(a.begin(),a.end());
    auto cut=[&](ll x){
        auto it=dat.lower_bound(x);
        if(it->first>x){
            dat[x]=it->second;
            it->second.first=x+1;
        }
    };
    for(auto [u,v]:a){
        auto [ux,uy]=u;
        auto [vx,vy]=v;
        cut(vy);
        cut(uy-1);
        ll mx=-INF;
        for(auto it=dat.lower_bound(uy);it->first<=vy;it=dat.erase(it)){
            mx=max(mx,it->second.second);
        }
        mx+=vx-ux+pad;
        dat[vy]={uy,mx};
        ans=max(ans,mx);
    }
    cout << max(0LL,(mxx-ans)*(mxy-mny)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}