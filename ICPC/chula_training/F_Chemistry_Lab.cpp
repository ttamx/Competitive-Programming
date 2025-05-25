#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<tuple<ll,ll,ll>> a(n);
    for(auto &[x,w,c]:a)cin >> x >> w >> c;
    sort(a.begin(),a.end());
    vector<double> dp(n);
    for(int i=0;i<n;i++){
        auto [xi,wi,ci]=a[i];
        dp[i]=-wi;
        for(int j=0;j<i;j++){
            auto [xj,wj,cj]=a[j];
            dp[i]=max(dp[i],dp[j]+(xi-xj)*(ci+cj)*k/200.0-wi);
        }
    }
    cout << fixed << setprecision(15) << max(0.0,*max_element(dp.begin(),dp.end())) << "\n";
}