#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=6005;

int n,ml,q;
ll t;
vector<tuple<ll,ll,ll>> a;

ll calc(ll lv){
    ll last=0;
    priority_queue<pair<ll,ll>> pq;
    for(auto [s,h,p]:a){
        ll diff=s-last;
        while(!pq.empty()&&diff>0){
            auto [pp,hh]=pq.top();
            pq.pop();
            if(diff<hh){
                hh-=diff;
                diff=0;
                pq.emplace(pp,hh);
            }else{
                diff-=hh;
            }
        }
        pq.emplace(p,h*lv);
        last=s;
    }
    ll res=0;
    while(!pq.empty()){
        auto [p,h]=pq.top();
        pq.pop();
        res+=p*h;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> ml >> t;
    a.resize(n);
    for(auto &[s,h,p]:a){
        cin >> s >> h >> p;
    }
    sort(a.begin(),a.end());
    a.emplace_back(t,0,0);
    cin >> q;
    while(q--){
        ll k;
        cin >> k;
        int l=0,r=ml;
        while(l<r){
            int m=(l+r+1)/2;
            if(calc(m)<=k)l=m;
            else r=m-1;
        }
        cout << l << "\n";
    }
}