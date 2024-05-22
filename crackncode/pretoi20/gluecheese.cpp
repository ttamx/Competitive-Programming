#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<ll,int,int>;

const int N=1005;
const ll INF=LLONG_MAX/2;

int n,m,cx,cy;
int t[N][N];
ll dp[N][N],dp2[N][N];
priority_queue<T,vector<T>,greater<T>> pq,pq2;

void go(int i,int j,ll d){
    d+=t[i][j];
    if(d>=dp[i][j])return;
    dp[i][j]=d;
    pq.emplace(d,i,j);
}

void go2(int i,int j,ll d){
    d+=t[i][j];
    if(d>=dp2[i][j])return;
    dp2[i][j]=d;
    pq2.emplace(d,i,j);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> cx >> cy;
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cin >> t[i][j];
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)dp[i][j]=INF;
    for(auto i:{1,n})for(auto j:{1,m})go(i,j,0);
    while(!pq.empty()){
        auto [d,i,j]=pq.top();
        pq.pop();
        if(d>dp[i][j])continue;
        go(i+1,j,d);
        go(i,j+1,d);
        go(i-1,j,d);
        go(i,j-1,d);
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)dp2[i][j]=INF;
    go2(cx,cy,-t[cx][cy]);
    while(!pq2.empty()){
        auto [d,i,j]=pq2.top();
        pq2.pop();
        if(d>dp2[i][j])continue;
        go2(i+1,j,d);
        go2(i,j+1,d);
        go2(i-1,j,d);
        go2(i,j-1,d);
    }
    for(int i=1;i<=n;i++)for(int j=1;j<=m;j++)cout << dp2[i][j]+dp[cx][cy] << " \n"[j==m];
}