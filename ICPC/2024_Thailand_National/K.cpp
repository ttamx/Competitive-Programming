#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<int> suf(n+1);
    for(int i=n-1;i>=0;i--){
        suf[i]=suf[i+1]+*max_element(a[i].begin(),a[i].end());
    }
    int k=9*n;
    vector<int> dp(k+1,-1);
    dp[a[0][0]]=a[0][m-1];
    int ans=max((a[0][0]+suf[1])*a[0][m-1],a[0][0]*(a[0][m-1]+suf[1]));
    for(int i=1;i<n;i++){
        vector<int> ndp(k+1,-1);
        vector<int> aux(10,-1);
        int mx=a[i][m-1];
        for(int j=m-2;j>=0;j--){
            aux[a[i][j]]=max(aux[a[i][j]],mx);
            mx=max(mx,a[i][j]);
        }
        for(int x=0;x<10;x++){
            if(aux[x]<0){
                continue;
            }
            for(int j=x;j<=k;j++){
                if(dp[j-x]>=0){
                    ndp[j]=max(ndp[j],dp[j-x]+aux[x]);
                }
            }
        }
        swap(dp,ndp);
        for(int j=0;j<=k;j++){
            if(dp[j]>=0){
                ans=max({ans,(j+suf[i+1])*dp[j],j*(dp[j]+suf[i+1])});
            }
        }
    }
    cout << ans;
}