#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int g,n,ans;
vector<tuple<ll,ll,ll>> v;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> g >> n;
    v.resize(g);
    for(auto &[t,x,y]:v)cin >> x >> y >> t;
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++){
        ll x,y,t;
        cin >> x >> y >> t;
        auto it=lower_bound(v.begin(),v.end(),make_tuple(t,-1e18,-1e18));
        bool ok=false;
        if(it!=v.end()){
            auto [t2,x2,y2]=*it;
            ll dt=(t-t2)*(t-t2);
            ll dx=(x-x2)*(x-x2);
            ll dy=(y-y2)*(y-y2);
            if(dx+dy>dt)ok=true;
        }
        it=upper_bound(v.begin(),v.end(),make_tuple(t,1e18,1e18));
        if(it!=v.begin()){
            it=prev(it);
            auto [t2,x2,y2]=*it;
            ll dt=(t-t2)*(t-t2);
            ll dx=(x-x2)*(x-x2);
            ll dy=(y-y2)*(y-y2);
            if(dx+dy>dt)ok=true;
        }
        ans+=ok;
    }
    cout << ans;
}