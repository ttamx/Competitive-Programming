#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<pair<pair<int,int>,pair<int,int>>> a(n);
    for(auto &[b,c]:a){
        cin >> b.first >> b.second >> c.first >> c.second;
    }
    map<int,vector<tuple<int,int,int>>> mp;
    for(int i=0;i<n;i++){
        auto [b,c]=a[i];
        auto [x1,y1]=b;
        auto [x2,y2]=c;
        mp[y1].emplace_back(x1,x2,i);
    }
    for(auto &[_,v]:mp){
        sort(v.begin(),v.end());
    }
    bool ok=true;
    function<pair<ll,ll>(int)> solve=[&](int u)->pair<ll,ll> {
        auto [b,c]=a[u];
        auto [x1,y1]=b;
        auto [x2,y2]=c;
        ll w=(x2-x1)*(y2-y1);
        ll x=(x1+x2)*w;
        if(mp.count(y2)){
            auto &d=mp[y2];
            while(!d.empty()&&get<0>(d.back())<=x2&&x1<=get<1>(d.back())){
                int v=get<2>(d.back());
                d.pop_back();
                auto [cw,cx]=solve(v);
                if(x1*cw*2>cx||x2*cw*2<cx)ok=false;
                w+=cw,x+=cx;
            }
        }
        return {w,x};
    };
    for(auto [x1,x2,u]:mp[0])solve(u);
    cout << (ok?"Stable":"Unstable") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}