#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5005;

int a[N];
int mx[15][N],mn[15][N],dp[N][N],lg[N];

int rmxq(int l,int r){
    if(l>r)return -2e9;
    int k=lg[r-l+1];
    return max(mx[k][l],mx[k][r-(1<<k)+1]);
}

int rmnq(int l,int r){
    if(l>r)return 2e9;
    int k=lg[r-l+1];
    return min(mn[k][l],mn[k][r-(1<<k)+1]);
}

void runcase(){
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=2;i<=n;i++)lg[i]=lg[i/2]+1;
    ll ans=0;
    for(int i=1;i<=n;i++)mx[0][i]=mn[0][i]=a[i];
    for(int i=1;i<15;i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            mx[i][j]=max(mx[i-1][j],mx[i-1][j+(1<<(i-1))]);
            mn[i][j]=min(mn[i-1][j],mn[i-1][j+(1<<(i-1))]);
        }
    }
    for(int i=1;i<=n;i++){
        int idx=i;
        dp[i][i]=0;
        for(int j=i-1;j>=1;j--){
            while(rmxq(j,idx-1)>=rmnq(idx,i))idx--;
            dp[j][i]=dp[j][idx-1]+(i-idx);
            ans+=dp[j][i];
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}