#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    map<ll,vector<ll>> mp;
    for(int i=0;i<n;i++){
        ll t,c;
        cin >> t >> c;
        mp[t].emplace_back(c);
    }
    for(auto &[t,v]:mp){
        if(v.size()>2){
            cout << -1 << "\n";
            return;
        }
        sort(v.begin(),v.end());
    }
    ll X=1e9;
    auto check=[&](ll d){
        pair<ll,ll> a(0,X),b(0,X);
        auto is_inside=[&](pair<ll,ll> p,ll x){
            return p.first<=x&&x<=p.second;
        };
        ll p=0;
        for(auto &[t,v]:mp){
            ll dif=(t-p)*d;
            a.first-=dif,a.second+=dif;
            b.first-=dif,b.second+=dif;
            if(v.size()==2){
                if(!(is_inside(a,v[0])&&is_inside(b,v[1]))&&!(is_inside(a,v[1])&&is_inside(b,v[0]))){
                    return false;
                }
                a={v[0],v[0]};
                b={v[1],v[1]};
            }else{
                if(is_inside(a,v[0])&&is_inside(b,v[0])){
                    a.first=min(a.first,b.first);
                    a.second=max(a.second,b.second);
                    b={v[0],v[0]};
                }else if(is_inside(a,v[0])){
                    a={v[0],v[0]};
                }else if(is_inside(b,v[0])){
                    b={v[0],v[0]};
                }else{
                    return false;
                }
            }
            p=t;
        }
        return true;
    };
    ll l=0,r=X;
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}