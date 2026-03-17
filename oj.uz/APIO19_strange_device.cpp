#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll LIM=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll a,b;
    cin >> n >> a >> b;
    ll c=b*min(a/gcd(a,b+1),LIM/b+1);
    map<ll,int> mp;
    auto insert=[&](ll l,ll r){
        mp[l]++;
        mp[r+1]--;
    };
    while(n--){
        ll l,r;
        cin >> l >> r;
        if(r-l+1>=c)insert(0,c-1);
        else{
            l%=c,r%=c;
            if(l<=r)insert(l,r);
            else insert(0,r),insert(l,c-1);
        }
    }
    ll ans=0,bal=0,last=0;
    for(auto [x,v]:mp){
        if(bal>0)ans+=x-last;
        last=x;
        bal+=v;
    }
    cout << ans << "\n";
}