#include<bits/stdc++.h>
 
using namespace std;
 
const int L=26;
const int N=5e5+5;
const int MOD=1e9+7;

int n,m;
int dp[N][L+2];
int aux[N][L+2][2];
vector<pair<int,int>> a[2];
int pre[N][2];

int norm(int x){
    if(x<0)x+=MOD;
    if(x>=MOD)x-=MOD;
    return x;
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        a[l>r].emplace_back(max(l,r),min(l,r));
    }
    for(int t=0;t<2;t++){
        sort(a[t].begin(),a[t].end());
        priority_queue<int> pq;
        pq.emplace(0);
        for(int i=n;i>=1;i--){
            while(!a[t].empty()&&a[t].back().first>=i){
                pq.emplace(a[t].back().second);
                a[t].pop_back();
            }
            while(pq.top()>=i){
                pq.pop();
            }
            pre[i][t]=pq.top();
        }
    }
    for(int i=1;i<=L;i++){
        dp[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        for(int j=1;j<=L;j++){
            aux[i-1][j][0]=norm(aux[i-1][j-1][0]+dp[i-1][j]);
        }
        for(int j=L;j>=1;j--){
            aux[i-1][j][1]=norm(aux[i-1][j+1][1]+dp[i-1][j]);
        }
        for(int j=1;j<=L;j++){
            dp[i][j]=norm(aux[i-1][L][0]-norm(aux[pre[i][0]][j-1][0]+aux[pre[i][1]][j+1][1]));
        }
    }
    int ans=0;
    for(int i=1;i<=L;i++){
        ans=norm(ans+dp[n][i])%MOD;
    }
    cout << ans;
}