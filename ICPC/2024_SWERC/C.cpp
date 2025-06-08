#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF=INT_MAX/2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    string s,t;
    cin >> s >> t;
    s=" "+s,t=" "+t;
    int ans=n;
    vector<vector<array<int,2>>> dp(n+1,vector<array<int,2>>(n+1,{-INF,-INF}));
    dp[0][0]={0,0};
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            int sz=i-j;
            string str=s.substr(j+1,sz)+t;
            int nn=str.size();
            vector<int> z(nn);
            z[0]=nn;
            for(int i=1,l=0,r=0;i<nn;i++){
                if(i<r)z[i]=min(z[i-l],r-i);
                while(str[i+z[i]]==str[z[i]])z[i]++;
                if(i+z[i]>r)l=i,r=i+z[i];
            }
            vector<int> nxt(m+2);
            nxt[m+1]=m+1;
            for(int i=m;i>=1;i--){
                nxt[i]=z[sz+i]>=sz?i:nxt[i+1];
            }
            for(int k=0;k<=j;k++){
                if(dp[j][k][1]>=0){
                    dp[i][k+sz][0]=max(dp[i][k+sz][0],nxt[min(dp[j][k][1],m)+1]);
                    if(j==0&&nxt[1]!=1)dp[i][k+sz][0]=m+1;
                    if(i==n&&nxt[m-sz+1]!=m-sz+1)ans=min(ans,k+sz);
                }
                dp[i][k+1][1]=max(dp[i][k+1][1],dp[j][k][0]);
            }
        }
    }
    for(int i=1;i<=n;i++){
        if(dp[n][i][1]>m){
            ans=min(ans,i);
        }
    }
    cout << ans << "\n";
}