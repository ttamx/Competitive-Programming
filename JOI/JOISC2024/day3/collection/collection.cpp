#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=25;

int n,q;
set<pair<int,int>> dp[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int a,b;
        cin >> a >> b;
        dp[i][i].emplace(a,b);
    }
    for(int sz=2;sz<=n;sz++){
        for(int l=1,r=sz;r<=n;l++,r++){
            for(int m=l;m<r;m++){
                for(auto [a,b]:dp[l][m]){
                    for(auto [c,d]:dp[m+1][r]){
                        dp[l][r].emplace(min(a,b),min(c,d));
                        dp[l][r].emplace(max(a,b),max(c,d));
                    }
                }
            }
        }
    }
    for(auto [a,b]:dp[1][n])cerr << a << " " << b << "\n";
    for(int i=1;i<=q;i++){
        int a,b;
        cin >> a >> b;
        if(dp[1][n].find({a,b})!=dp[1][n].end())cout << i << " ";
    }
    cout << "\n";
}