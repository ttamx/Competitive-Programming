#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll L=2e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<ll,pair<ll,ll>> dat;
    dat[L]={0,0};
    auto split=[&](ll x){
        auto it=dat.lower_bound(x);
        auto &[p,v]=it->second;
        if(p<x){
            dat[x-1]={p,v};
            p=x;
        }
    };
    auto add=[&](ll l,ll r,ll val){
        split(l);
        split(r+1);
        auto it=dat.find(r);
        assert(it!=dat.end());
        auto &[p,v]=it->second;
        assert(p==l);
        v+=val;
        if(it!=dat.begin()&&prev(it)->second.second==v){
            it->second=prev(it)->second;
            dat.erase(prev(it));
        }
        if(next(it)!=dat.end()&&next(it)->second.second==v){
            next(it)->second=it->second;
            dat.erase(it);
        }
    };
    for(int i=0;i<n;i++){
        char c;
        ll x,len;
        cin >> c >> len >> x;
        if(c=='|'){
            add(x,x,len);
            cout << "S";
        }else{
            ll l=x,r=x+len-1;
            auto it=dat.lower_bound(r);
            if(it->second.first<=l){
                add(l,r,+1);
                cout << "S";
            }else{
                cout << "U";
            }
        }
    }
}