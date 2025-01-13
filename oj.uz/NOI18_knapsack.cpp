#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int s,n;
    cin >> s >> n;
    vector<vector<pair<int,int>>> a(s+1);
    for(int i=0;i<n;i++){
        int v,w,k;
        cin >> v >> w >> k;
        a[w].emplace_back(v,k);
    }
    vector<pair<int,int>> b;
    for(int w=1;w<=s;w++){
        sort(a[w].rbegin(),a[w].rend());
        int cur=0;
        for(auto [v,k]:a[w]){
            for(int j=0;j<k;j++){
                if(cur+w>s)break;
                cur+=w;
                b.emplace_back(w,v);
            }
        }
    }
    vector<int64_t> dp(s+1);
    for(auto [w,v]:b){
        for(int i=s;i>=w;i--){
            dp[i]=max(dp[i],dp[i-w]+v);
        }
    }
    cout << dp[s];
}