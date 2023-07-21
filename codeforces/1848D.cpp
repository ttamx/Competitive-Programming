#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    ll s,k;
    cin >> s >> k;
    ll ans=s*k;
    s+=s%10;
    k--;
    ans=max(ans,s*k);
    if(s%10==0)return void(cout << ans << "\n");
    for(int i=0;i<4&&k>=0;i++){
        auto calc=[&](ll x){
            return (s+20*x)*(k-4*x);
        };
        ll x=(5*k-s)/40;
        x=max(x,0ll);
        x=min(x,k/4);
        ans=max(ans,calc(x));
        if(x<k/4)ans=max(ans,calc(x+1));
        s+=s%10;
        k--;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}