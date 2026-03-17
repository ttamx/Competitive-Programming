#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=505;
const int A=15;
const int M=1<<A;
const int INF=1e9;

int n;
int a[N];
int dp[N][M];
vector<int> vals;
int ans=INF;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        vals.emplace_back(a[i]);
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(vals.begin(),vals.end(),a[i])-vals.begin();
    }
    for(int j=1;j<M;j++){
        dp[0][j]=INF;
    }
    for(int i=1;i<=n;i++){
        for(int j=0;j<M;j++){
            dp[i][j]=INF;
        }
        for(int j=0;j<M;j++){
            int pos=-1;
            for(int k=a[i];k>=0;k--){
                if(j>>k&1){
                    pos=k;
                    break;
                }
            }
            if(pos==-1){
                int mask=j^(1<<a[i]);
                dp[i][mask]=min(dp[i][mask],dp[i-1][j]+1);
                if(i>1){
                    dp[i][mask]=min(dp[i][mask],dp[i-2][j]+1);
                }
            }else{
                int mask=j^(1<<a[i])^(1<<pos);
                dp[i][mask]=min(dp[i][mask],dp[i-1][j]);
                if(i>1){
                    dp[i][mask]=min(dp[i][mask],dp[i-2][j]);
                }
            }
        }
    }
    for(int i=n-1;i<=n;i++){
        for(int j=0;j<M;j++){
            ans=min(ans,dp[i][j]);
        }
    }
    cout << ans << "\n";
}