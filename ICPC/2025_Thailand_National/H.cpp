#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll MOD=1e9+7;

ll psum(ll n){
    n%=MOD;
    return n*(n+1)/2%MOD;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll n;
        cin >> n;
        n*=2;
        vector<ll> c{n/5};
        for(ll m=n;m/=5;){
            c.back()-=m;
            c.emplace_back(m);
        }
        ll ans=0;
        for(int i=c.size()-1;i>=1;i--){
            ll req=c[i];
            ll cur=n;
            cur-=req/4*5;
            req%=4;
            while(req>0){
                if(cur%5)req--;
                cur--;
            }
            ans=(ans+(psum(n)-psum(cur)-(psum(n/5)-psum(cur/5)+MOD)*5+MOD)%MOD*i%MOD+2*MOD)%MOD;
            n=cur;
        }
        cout << ans << "\n";
    }
}