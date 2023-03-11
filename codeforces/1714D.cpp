#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    int n;
    cin >> s >> n;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<pair<int,vector<pair<int,int>>>> dp(s.size()+1,{2e9,vector<pair<int,int>>(0)});
    dp[0].first=0;
    for(int i=0;i<s.size();i++){
        for(int k=0;k<n;k++){
            auto x=a[k];
            if(s.substr(i,x.size())==x){
                for(int j=i+1;j<=min(i+x.size(),s.size());j++){
                    if(dp[j].first<dp[i].first+1)continue;
                    dp[j]=dp[i];
                    dp[j].first++;
                    dp[j].second.push_back({k+1,i+1});
                }
            }
        }
    }
    if(dp[s.size()].first==2e9){
        cout << -1 << '\n';
        return;
    }
    cout << dp[s.size()].first << '\n';
    for(auto [x,y]:dp[s.size()].second)cout << x << ' ' << y << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}