#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int q;
    cin >> q;
    vector<vector<tuple<int,int,int>>> qr(n);
    for(int i=0;i<q;i++){
        int l,r,x;
        cin >> l >> r >> x;
        l--,r--;
        qr[r].emplace_back(l,x,i);
    }
    vector<int> ans(q);
    vector<vector<int>> dp(1<<12,vector<int>(13,-1));
    dp[0][0]=n;
    for(int i=0;i<n;i++){
        for(int c=12;c>=1;c--){
            for(int j=0;j<1<<12;j++){
                dp[j][c]=max(dp[j][c],min(dp[j^a[i]][c-1],i));
            }
        }
        for(auto [l,x,j]:qr[i]){
            for(int c=1;c<=12;c++){
                if(dp[x][c]>=l){
                    ans[j]=c;
                    break;
                }
            }
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}