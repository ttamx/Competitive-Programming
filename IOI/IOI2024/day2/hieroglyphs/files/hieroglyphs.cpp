#include <bits/stdc++.h>

using namespace std;

const int N=3005;

int dp[N][N];

vector<int> ucs(vector<int> a,vector<int> b){
    int n=a.size(),m=b.size();
    if(n>3000||m>3000){
        if(a==b)return a;
        return {-1};
    }
    a.insert(a.begin(),0);
    b.insert(b.begin(),0);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            if(a[i]==b[j]){
                dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
            }
        }
    }
    vector<int> ans;
    vector<int> c(n+2),d(m+2);
    int cnt=dp[n][m];
    for(int i=n,j=m;i>0&&j>0;){
        if(a[i]==b[j]&&dp[i][j]==dp[i-1][j-1]+1){
            ans.emplace_back(a[i]);
            c[i]=cnt;
            d[j]=cnt;
            cnt--;
            i--,j--;
        }else if(dp[i][j]==dp[i-1][j]){
            i--;
        }else if(dp[i][j]==dp[i][j-1]){
            j--;
        }else{
            assert(false);
        }
    }
    reverse(ans.begin(),ans.end());
    {
        int l=1;
        for(int i=1;i<=n;i++){
            int r=ans.size();
            multiset<int> ms;
            for(int j=l;j<=ans.size();j++){
                ms.emplace(ans[j-1]);
            }
            if(ms.empty()){
                break;
            }
            for(int j=m;j>=1;j--){
                if(a[i]==b[j]){
                    if(ms.find(a[i])==ms.end()){
                        return {-1};
                    }
                }
                if(d[j]){
                    r=d[j]-1;
                    ms.erase(ms.find(ans[r]));
                    if(ms.empty()){
                        break;
                    }
                }
            }
            if(c[i]){
                l=c[i]+1;
            }
        }
    }
    {
        int l=1;
        for(int i=1;i<=m;i++){
            int r=ans.size();
            multiset<int> ms;
            for(int j=l;j<=ans.size();j++){
                ms.emplace(ans[j-1]);
            }
            if(ms.empty()){
                break;
            }
            for(int j=n;j>=1;j--){
                if(b[i]==a[j]){
                    if(ms.find(b[i])==ms.end()){
                        return {-1};
                    }
                }
                if(c[j]){
                    r=c[j]-1;
                    ms.erase(ms.find(ans[r]));
                    if(ms.empty()){
                        break;
                    }
                }
            }
            if(d[i]){
                l=d[i]+1;
            }
        }
    }
    return ans;
}
