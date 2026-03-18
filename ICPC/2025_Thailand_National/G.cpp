#pragma GCC optimize("Ofast, unroll-loops")
#include<bits/stdc++.h>

using namespace std;

const int K=10005;
const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> a(n);
    for(auto &[l,r,k]:a){
        cin >> l >> r >> k;
    }
    sort(a.begin(),a.end());
    a.emplace_back(86400,86399,0);
    array<pair<int,int>,K> dp;
    fill(dp.begin(),dp.end(),make_pair(-INF,0));
    dp[0]={0,0};
    int last=-1;
    for(auto [l,r,k]:a){
        array<pair<int,int>,K> ndp;
        fill(ndp.begin(),ndp.end(),make_pair(-INF,0));
        for(auto &[x,y]:dp){
            y+=l-last-1;
            x+=y/m;
            y%=m;
        }
        last=r;
        for(int i=0;i<K;i++){
            ndp[min(i+k,K-1)]=max(ndp[min(i+k,K-1)],{dp[i].first,0});
        }
        for(int i=k;i<K;i++){
            auto res=dp[i];
            res.second+=r-l+1;
            res.first+=res.second/m;
            res.second%=m;
            ndp[i-k]=max(ndp[i-k],res);
        }
        dp=move(ndp);
    }
    cout << max_element(dp.begin(),dp.end())->first;
}