#include<bits/stdc++.h>

using namespace std;

using ll = long long;

using db = long double;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<pair<ll,ll>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    sort(a.begin(),a.end());
    db ans=1e100;
    for(int i=0;i+k-1<n;i++){
        db dx=a[i].first-a[i+k-1].first;
        db dy=a[i].second-a[i+k-1].second;
        ans=min(ans,dx*dx+dy*dy);
    }
    cout << fixed << setprecision(20) << ans*acos(db(-1))/4.0;
}