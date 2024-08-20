#include<bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));
 
void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x,x--;
    vector<vector<int>> dp(n,vector<int>(n,INF));
    for(int i=0;i<n-1;i++)if(a[i]<=i&&(i-a[i])%2==0){
        dp[i][i+1]=(i-a[i])/2;
    }
    for(int sz=4;sz<=n;sz+=2){
        for(int l=0,r=sz-1;r<n;l++,r++){
            if(l<a[l]||(l-a[l])%2)continue;
            int x=(l-a[l])/2;
            if(dp[l+1][r-1]<=x)dp[l][r]=x;
            for(int m=l+1;m<r;m+=2){
                dp[l][r]=min(dp[l][r],max(dp[l][m],dp[m+1][r]-(m-l+1)/2));
            }
        }
    }
    vector<int> dp2(n+1);
    dp2[0]=0;
    for(int i=0;i<n;i++){
        dp2[i+1]=max(dp2[i+1],dp2[i]);
        for(int j=i+2;j<=n;j+=2){
            if(dp[i][j-1]<=dp2[i]){
                dp2[j]=max(dp2[j],dp2[i]+(j-i)/2);
            }
        }
    }
    cout << dp2[n] << "\n";
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}