#include<bits/stdc++.h>

using namespace std;

const int M=1005;

typedef long long ll;

const ll inf=1e18;

int n,m;
int a[M];
ll dp[M][M];
int opt[M][M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(cin >> n >> m){
        for(int i=1;i<=m;i++)cin >> a[i];
        a[m+1]=n;
        for(int i=0;i<=m;i++)dp[i][i+1]=0,opt[i][i+1]=i;
        for(int sz=2;sz<=m+1;sz++){
            for(int l=0,r=sz;r<=m+1;l++,r++){
                pair<ll,int> best(inf,-1);
                for(int k=max(l+1,opt[l][r-1]);k<=min(r-1,opt[l+1][r]);k++)best=min(best,{dp[l][k]+dp[k][r],k});
                tie(dp[l][r],opt[l][r])=best;
                dp[l][r]+=a[r]-a[l];
            }
        }
        cout << dp[0][m+1] << "\n";
    }
}