#include <bits/stdc++.h>

using namespace std;

using P = pair<int,int>;

const int N=1e5+5;
const int INF=INT_MAX/2;

int n,m;
int s[N],f[N];
pair<int,int> dp[N][2];

bool check(int x){
    int a=1,b=1,c=1;
    dp[0][0]=dp[0][1]={1,0};
    for(int i=1;i<=n;i++){
        while(a<=m&&f[a]<=s[i])a++;
        while(b<=m&&f[b]<=s[i-1]+x)b++;
        while(c<=m&&f[c]<=s[i]+x)c++;
        dp[i][0]=dp[i][1]=max(P(dp[i-1][0].first,0),P(dp[i-1][1].first,1));
        if(f[dp[i-1][0].first]>=s[i]-x)dp[i][0]=max(dp[i][0],P(a,0));
        if(f[dp[i-1][1].first]>=s[i]-x)dp[i][0]=max(dp[i][0],P(max(a,b),1));
        if(f[dp[i-1][0].first]>=s[i])dp[i][1]=max(dp[i][1],P(c,0));
        if(f[dp[i-1][1].first]>=s[i])dp[i][1]=max(dp[i][1],P(c,1));
    }
    return max(dp[n][0],dp[n][1]).first>m;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> s[i];
    for(int i=1;i<=m;i++)cin >> f[i];
    s[0]=-INF;
    f[m+1]=INF;
    int l=0,r=INF;
    while(l<r){
        int md=(l+r)/2;
        if(check(md))r=md;
        else l=md+1;
    }
    if(l==INF)cout << -1 << "\n";
    else{
        check(l);
        string ans(n,' ');
        for(int i=n,j=dp[n][1]>dp[n][0];i>=1;i--){
            ans[i-1]="LR"[j];
            j=dp[i][j].second;
        }
        cout << l << "\n";
        cout << ans << "\n";
    }
}