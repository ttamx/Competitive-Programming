#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll isqrt(ll x){
    assert(x>=0);
    ll v=sqrt(x)+2;
    while(v*v>x)v--;
    return v;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll r,w,h;
        cin >> r >> w >> h;
        if(w*w+h*h>4*r*r){
            cout << 0 << "\n";
            continue;
        }
        ll ans=0;
        for(int t=0;t<2;t++){
            auto f=[&](ll x){
                return isqrt((4*r*r-x*x*w*w)/(h*h));
            };
            ll st=r*sqrt(2)/w;
            for(ll i=max(st-10000,1LL);i<=st+10000;i++){
                if(i*i*w*w+h*h>4*r*r)break;
                ans=max(ans,i*f(i));
            }
            swap(h,w);
        }
        cout << ans << "\n";
    }
}