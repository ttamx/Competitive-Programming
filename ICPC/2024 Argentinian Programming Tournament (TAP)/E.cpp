#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,p;
    cin >> n >> p;
    vector<tuple<int,int,int>> w(n);
    for(auto &[a,b,c]:w)cin >> a >> b >> c;
    sort(w.begin(),w.end(),[&](tuple<int,int,int> x,tuple<int,int,int> y){
        auto [xa,xb,xc]=x;
        auto [ya,yb,yc]=y;
        return 1LL*ya*xb+yb>1LL*yb*xa+xb;
    });
    vector<int> dp(p+1);
    for(auto [a,b,c]:w){
        auto ndp=dp;
        for(int i=b;i<=p;i++){
            int np=(i-b)/a;
            ndp[np]=max(ndp[np],dp[i]+c);
        }
        swap(dp,ndp);
    }
    cout << *max_element(dp.begin(),dp.end());
}