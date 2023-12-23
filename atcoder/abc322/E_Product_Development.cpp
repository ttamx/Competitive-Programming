#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int n,k,p;
ll dp[6][6][6][6][6];
int a[105][6];
int v[6],c[105];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> p;
    for(int i=0;i<n;i++){
        cin >> c[i];
        for(int j=0;j<k;j++){
            cin >> a[i][j];
        }
    }
    for(int i=0;i<k;i++)v[i]=p;
    for(int i=p;i>=0;i--)for(int j=p;j>=0;j--)for(int k=p;k>=0;k--)for(int l=p;l>=0;l--)for(int m=p;m>=0;m--)dp[i][j][k][l][m]=1e18;
    dp[0][0][0][0][0]=0;
    for(int pp=0;pp<n;pp++){
        for(int i=p;i>=0;i--)for(int j=p;j>=0;j--)for(int k=p;k>=0;k--)for(int l=p;l>=0;l--)for(int m=p;m>=0;m--){
            auto &x=dp[i][j][k][l][m];
            auto &y=dp[min(p,i+a[pp][0])][min(p,j+a[pp][1])][min(p,k+a[pp][2])][min(p,l+a[pp][3])][min(p,m+a[pp][4])];
            y=min(y,x+c[pp]);
        }
    }
    ll ans=dp[v[0]][v[1]][v[2]][v[3]][v[4]];
    cout << (ans==1e18?-1:ans);
}