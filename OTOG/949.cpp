#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    map<ll,ll> mp;
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            ll l,r;
            cin >> l >> r;
            auto it=mp.upper_bound(l);
            if(it!=mp.begin()&&prev(it)->second>=r)continue;
            mp[l]=r;
            it=mp.find(l);
            for(;next(it)!=mp.end()&&next(it)->first<=it->second+1;mp.erase(next(it))){
                it->second=max(it->second,next(it)->second);
            }
            for(;it!=mp.begin()&&(--it)->second+1>=next(it)->first;mp.erase(next(it))){
                it->second=max(it->second,next(it)->second);
            }
        }else{
            cout << mp.size() << "\n";
        }
    }
}