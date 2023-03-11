#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1005;
const int W=10005;

int n;
int w[N],s[N];
ll v[N],dp[N][W];
vector<tuple<int,int,int,int>> vc;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    vc.resize(n);
    for(auto &[u,x,y,z]:vc)cin >> x >> y >> z,u=x+y;
    sort(vc.begin(),vc.end());
    for(int i=0;i<n;i++)tie(w[0],w[i+1],s[i+1],v[i+1])=vc[i];
    ll ans=0;
    for(int i=1;i<=n;i++){
        for(int j=0;j<W;j++)dp[i][j]=dp[i-1][j];
        for(int j=0;j<=s[i];j++){
            if(j+w[i]<W)dp[i][j+w[i]]=max(dp[i][j+w[i]],dp[i-1][j]+v[i]);
            ans=max(ans,dp[i-1][j]+v[i]);
        }
    }
    cout << ans;
}