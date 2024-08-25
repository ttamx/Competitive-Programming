#include<bits/stdc++.h>

using namespace std;

const int INF=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector dp(n+1,vector(n+1,vector<tuple<int,int,int>>(n+1,{-INF,-1,-1})));
    dp[0][0][0]={0,-1,-1};
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=j;k++){
                for(int l=0;l<=k;l++){
                    dp[i][j][k]=max(dp[i][j][k],{get<0>(dp[i-1][j-k][l])+l,j-k,l});
                }
            }
        }
    }
    vector<int> a;
    tuple<int,int,int> best(-INF,-1,-1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            best=max(best,{min(n-i,get<0>(dp[i][n][j])),i,j});
        }
    }
    auto [ans,i,p]=best;
    if(ans<k){
        cout << "NO\n";
        exit(0);
    }
    int j=n;
    for(;i>0;i--){
        auto [val,x,y]=dp[i][j][p];
        a.emplace_back(p);
        j=x,p=y;
    }
    reverse(a.begin(),a.end());
    vector<pair<int,int>> b,c;
    int pos=1;
    for(auto x:a){
        for(int i=1;i<x;i++){
            b.emplace_back(pos,pos+1);
            pos++;
        }
        pos++;
    }
    pos=1;
    for(int i=0;i+1<a.size();i++){
        for(int j=0;j<a[i];j++){
            c.emplace_back(pos,pos+a[i]);
            pos++;
        }
    }
    cout << "YES\n";
    for(int i=0;i<k;i++)cout << b[i].first << " " << b[i].second << "\n";
    for(int i=0;i<k;i++)cout << c[i].first << " " << c[i].second << "\n";
}