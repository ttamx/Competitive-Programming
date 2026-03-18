#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5005;
const int INF=INT_MAX/2;

int n;
ll a[N];
int dp[N][N],pre[N][N];
int ans=0,idx=0;
vector<ll> b;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]+=a[i-1];
    }
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            dp[i][j]=-INF;
        }
    }
    for(int i=1;i<=n;i++){
        int p=i+1;
        int mx=-INF,opt=-1;
        for(int j=i-1;j>=0;j--){
            while(p<=n&&a[p]-a[i]<a[i]-a[j]){
                dp[i][p]=mx;
                pre[i][p]=opt;
                p++;
            }
            if(dp[j][i]+1>mx){
                mx=dp[j][i]+1;
                opt=j;
            }
        }
        while(p<=n){
            dp[i][p]=mx;
            pre[i][p]=opt;
            p++;
        }
        if(i==n){
            if(mx>ans){
                ans=mx;
                idx=opt;
            }
        }
    }
    for(int i=n,j=idx;i>0;tie(i,j)=make_pair(j,pre[j][i])){
        b.emplace_back(a[i]-a[j]);
    }
    reverse(b.begin(),b.end());
    assert(b.size()==ans);
    cout << ans << "\n";
    for(auto x:b){
        cout << x << " ";
    }
    cout << "\n";
}