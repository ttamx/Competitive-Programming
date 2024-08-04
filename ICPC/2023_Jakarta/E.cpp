#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> a;
    int mx=0;
    for(int i=0;i<2*n;i++){
        int x;
        cin >> x;
        if(x>mx){
            mx=x;
            a.push_back({x});
        }else{
            a.back().emplace_back(x);
        }
    }
    vector<int> s;
    for(auto &x:a)s.emplace_back(x.size());
    int m=s.size();
    vector<vector<pair<int,int>>> dp(m+1,vector<pair<int,int>>(2*n+1));
    dp[0][0]={1,-1};
    for(int i=1;i<=m;i++){
        for(int j=0;j<=n;j++){
            if(dp[i-1][j].first){
                dp[i][j]={1,-1};
            }
            if(j>=s[i-1]&&dp[i-1][j-s[i-1]].first){
                dp[i][j]={1,i-1};
            }
        }
    }
    if(!dp[m][n].first){
        cout << -1;
        exit(0);
    }
    vector<int> b,c;
    vector<bool> used(m);
    for(int i=m,j=n;i>0;i--){
        int x=dp[i][j].second;
        if(x==-1){
            continue;
        }
        b.emplace_back(x);
        used[x]=true;
        j-=s[x];
    }
    reverse(b.begin(),b.end());
    for(int i=0;i<m;i++){
        if(!used[i]){
            c.emplace_back(i);
        }
    }
    for(auto i:b){
        for(auto x:a[i]){
            cout << x << " ";
        }
    }
    cout << "\n";
    for(auto i:c){
        for(auto x:a[i]){
            cout << x << " ";
        }
    }
    cout << "\n";
}