#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto calc=[&](ll lambda){
        array<pair<ll,int>,2> best;
        best[0]={0,0};
        best[1]={-1e18,0};
        ll sum=0;
        for(auto x:a){
            best[1]=max(make_pair(best[1].first+x,best[1].second),make_pair(best[0].first+x-lambda,best[0].second-1));
            best[0]=max(best[0],best[1]);
        }
        best[0].second*=-1;
        return best[0];
    };
    ll l=0,r=1e18;
    while(l<r){
        ll mid=l+(r-l)/2;
        if(calc(mid).second<=k)r=mid;
        else l=mid+1;
    }
    cout << calc(l).first+l*k;
}