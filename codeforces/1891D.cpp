#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int B=64;
const ll mod=1e9+7;
const ll inf=1e18;

vector<ll> vec[B];

void runcase(){
    ll l,r;
    cin >> l >> r;
    ll bl=63-__builtin_clzll(l);
    ll br=63-__builtin_clzll(r);
    ll ans=0;
    for(int b=bl;b<=br;b++){
        ll pr=min((2ll<<b)-1,r);
        auto it=prev(upper_bound(vec[b].begin(),vec[b].end(),l));
        ans+=(pr-l+1)%mod*(it-vec[b].begin());
        ans%=mod;
        while(it!=vec[b].end()&&*it<=pr){
            ans+=pr-max(l,*it)+1;
            ans%=mod;
            it++;
        }
        l=pr+1;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int b=2;b<60;b++){
        ll x=b;
        ll res=inf/b;
        while(res>0){
            vec[b].emplace_back(x);
            x*=b;
            res/=b;
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}