#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n,k,a,b;
    cin >> n >> k >> a >> b;
    vector<ll> c(k);
    for(auto &x:c)cin >> x;
    sort(c.begin(),c.end());
    auto rec=[&](auto &&self,ll l,ll r){
        ll cnt=upper_bound(c.begin(),c.end(),r)-lower_bound(c.begin(),c.end(),l);
        if(cnt==0)return a;
        ll res=cnt*b*(r-l+1);
        if(l<r){
            ll m=(l+r)/2;
            res=min(res,self(self,l,m)+self(self,m+1,r));
        }
        return res;
    };
    cout << rec(rec,1,1<<n) << "\n";
}