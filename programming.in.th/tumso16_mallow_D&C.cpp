#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,k;
int a[N],qs[N],val[N],dp[12][N];

void compute(int cur,int l,int r,int optl,int optr){
    if(l>r)return;
    int mid=(l+r)/2;
    pair<int,int> best={2e9,-1};
    for(int i=optl;i<=min(mid,optr);i++)best=min(best,{dp[cur-1][i-1]+(val[mid]-val[i])-i*(qs[mid]-qs[i]),i});
    int opt;
    tie(dp[cur][mid],opt)=best;
    compute(cur,l,mid-1,optl,opt);
    compute(cur,mid+1,r,opt,optr);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    for(int i=1;i<=n;i++)val[i]=val[i-1]+a[i]*i;
    for(int i=1;i<=n;i++)dp[1][i]=val[i]-qs[i];
    for(int i=2;i<=k;i++)compute(i,1,n,1,n);
    cout << dp[k][n];
}