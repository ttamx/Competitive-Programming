#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    map<int,int> mp;
    vector<pair<int,int>> vec(n);
    for(auto &[x,y]:vec){
        cin >> x >> y;
        mp[x],mp[y];
    }
    int m=0;
    for(auto &[x,y]:mp)y=++m;
    vector<int> dp(m+1,0);
    vector<vector<int>> r(m+1);
    for(int i=0;i<n;i++){
        auto &[x,y]=vec[i];
        x=mp[x];
        y=mp[y];
        r[y].emplace_back(i);
    }
    vector<int> cur;
    for(int i=1;i<=m;i++){
        dp[i]=dp[i-1];
        for(auto j:r[i]){
            for(auto k:cur){
                if(vec[k].second<vec[j].first)continue;
                dp[i]=max(dp[i],dp[min(vec[j].first,vec[k].first)-1]+2);
            }
            cur.emplace_back(j);
        }
    }
    cout << n-dp[m] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}