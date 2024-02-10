#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n+2),cnt(n);
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]--;
        cnt[a[i]]++;
    }
    int ans=0;
    for(int t=0;t<2;t++){
        vector<int> dp(n+2),dp2(n+2),pos(n),pos2(n),last(n);
        for(int i=1;i<=n;i++){
            last[a[i]]=i;
            if(!pos[a[i]])pos[a[i]]=i;
            else if(!pos2[a[i]])pos2[a[i]]=i;
        }
        for(int i=1;i<=n;i++){
            int c=a[i];
            dp[i]=dp[i-1];
            dp2[i]=dp2[i-1];
            if(i==last[c]){
                dp[i]=max(dp[i],dp[pos[c]-1]+cnt[c]);
                dp2[i]=max(dp2[i],dp2[pos[c]-1]+cnt[c]);
                if(pos2[c])dp2[i]=max(dp2[i],dp[pos2[c]-1]+cnt[c]-1);
            }
        }
        ans=max(ans,dp[n]);
        if(k)ans=max(ans,dp2[n]);
        reverse(a.begin(),a.end());
    }
    cout << n-ans;
}