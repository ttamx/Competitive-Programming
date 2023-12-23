#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int inf=1e9;

int n;
int h[N],dp[N];

double calc(int i,int j){
    return h[j]-h[i]+sqrt(i-j);
}

void solve(int l,int r,int optl,int optr){
    if(l>r)return;
    int mid=(l+r)/2;
    int opt=optl;
    for(int i=optl;i<=min(mid,optr);i++)if(calc(mid,i)>calc(mid,opt))opt=i;
    dp[mid]=max(dp[mid],(int)ceil(calc(mid,opt)));
    solve(l,mid-1,optl,opt);
    solve(mid+1,r,opt,optr);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> h[i];
    for(int t=0;t<2;t++){
        solve(1,n,1,n);
        reverse(h+1,h+n+1);
        reverse(dp+1,dp+n+1);
    }
    for(int i=1;i<=n;i++)cout << dp[i] << "\n"; 
}