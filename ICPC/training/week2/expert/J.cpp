#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    ll a,b,c,d,v,t;
    cin >> a >> b >> c >> d >> v >> t;
    vector<pair<ll,ll>> event;
    for(int i=0;i<c;i++){
        event.emplace_back(a*i,b);
    }
    for(int i=0;i<a;i++){
        event.emplace_back(c*i,d);
    }
    sort(event.begin(),event.end());
    ll last=-1e18;
    ll u=t/(a*c);
    ll ans=0;
    ll left=t-u*a*c;
    if(u==0){
        ll ans=0;
        for(auto [x,y]:event){
            if(x>t)break;
            ll cur=y-(x>last?1:0);
            ans+=cur;
            last=x+v;
        }
        cout << ans << "\n";
        return;
    }
    for(int t=0;t<2;t++){
        ll tot=0;
        for(auto [x,y]:event){
            if(t)x+=a*c;
            ll cur=y-(x>last?1:0);
            tot+=cur;
            if(t&&x-a*c<=left){
                ans+=cur;
            }
            last=x+v;
        }
        if(t==0){
            ans+=tot;
        }else{
            ans+=(u-1)*tot;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}