#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;
const int M=25;
const int K=(1<<20)+5;

int n,m;
pair<int,int> a[N];
int b[M];
pair<int,int> dp[K];
vector<int> ans[M];
int nxt[M][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> a[i].first,a[i].second=i;
    for(int i=0;i<m;i++)cin >> b[i];
    sort(a+1,a+n+1,greater<pair<int,int>>());
    for(int i=0;i<m;i++){
        for(int l=1,r=1;l<=n;r=max(r,++l)){
            while(r<=n&&1ll*a[r].first*(r-l+1)<b[i])r++;
            nxt[i][l]=r;
        }
    }
    for(int mask=1;mask<1<<m;mask++){
        dp[mask]={n+1,-1};
        for(int i=0;i<m;i++)if(mask>>i&1){
            int mask2=mask^(1<<i);
            int pos=dp[mask2].first;
            if(pos>=n)continue;
            int l=nxt[i][pos+1];
            if(l<=n)dp[mask]=min(dp[mask],{l,i});
        }
    }
    int mask=(1<<m)-1;
    int pos=dp[mask].first;
    if(pos>n){
        cout << "NO\n";
        return 0;
    }
    cout << "YES\n";
    while(mask>0){
        int id=dp[mask].second;
        int mask2=mask^(1<<id);
        for(int i=dp[mask2].first+1;i<=dp[mask].first;i++){
            ans[id].emplace_back(a[i].second);
        }
        mask=mask2;
    }
    for(int i=0;i<m;i++){
        cout << ans[i].size();
        for(auto x:ans[i])cout << " " << x;
        cout << "\n";
    }
}