#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> p2;

const ll inf=1e8;

void runcase(){
    int n;
    ll r,d;
    cin >> n >> r >> d;
    vector<p2> pts(n);
    for(auto &[x,y]:pts)cin >> x >> y;
    sort(pts.begin(),pts.end());
    ld cur=inf;
    multiset<p2> ms;
    int idx=0;
    auto pw2=[&](ll x){
        return x*x;
    };
    auto dist=[&](p2 x,p2 y){
        return sqrtl(pw2(x.first-y.first)+pw2(x.second-y.second));
    };
    for(auto [x,y]:pts){
        while(x-pts[idx].first>cur){
            ms.erase(ms.find(make_pair(pts[idx].second,pts[idx].first)));
            idx++;
        }
        for(auto it=ms.lower_bound(make_pair(y-cur,-inf));it!=ms.end()&&it->first<=y+cur;it++){
            cur=min(cur,dist(make_pair(x,y),make_pair(it->second,it->first)));
        }
        ms.emplace(y,x);
    }
    cout << (cur>=2*r+d?"Y":"N") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}