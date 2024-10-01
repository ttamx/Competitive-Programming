#include<bits/stdc++.h>

using namespace std;

using ll = long long;

mt19937 rng(9163974);

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
    }
    int ans=0;
    auto solve=[&](){
        vector<pair<ll,ll>> b;
        int p=rng()%n;
        for(int i=0;i<n;i++){
            if(i==p)continue;
            ll dx=a[i].first-a[p].first;
            ll dy=a[i].second-a[p].second;
            b.emplace_back(dx,dy);
        }
        sort(b.begin(),b.end(),[&](pair<ll,ll> x,pair<ll,ll> y){
            return x.first*y.second<x.second*y.first;
        });
        for(int i=0;i<n-1;){
            int j=i+1;
            while(j<n-1&&b[i].first*b[j].second==b[i].second*b[j].first){
                j++;
            }
            ans=max(ans,j-i);
            i=j;
        }
    };
    for(int i=0;i<30;i++)solve();
    cout << n-ans-1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}