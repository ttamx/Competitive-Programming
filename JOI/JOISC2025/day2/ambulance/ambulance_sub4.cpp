#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=20;

int n,l,t;
int x[N],y[N];
int cost[N];
ll dp[4][1<<N];

void calc(ll *dp,int x1,int y1){
    for(int i=0;i<n;i++){
        cost[i]=abs(x[i]-x1)+abs(y[i]-y1);
    }
    for(int mask=0;mask<1<<n;mask++){
        int sum=0;
        for(int i=0;i<n;i++){
            if(mask>>i&1){
                sum+=cost[i];
            }
        }
        dp[mask]=(sum<=t);
    }
}

void zeta(ll *a){
    for(int i=0;i<n;i++){
        for(int mask=0;mask<1<<n;mask++){
            if(mask>>i&1){
                a[mask]+=a[mask^(1<<i)];
            }
        }
    }
}

void mobius(ll *a){
    for(int i=n-1;i>=0;i--){
        for(int mask=0;mask<1<<n;mask++){
            if(mask>>i&1){
                a[mask]-=a[mask^(1<<i)];
            }
        }
    }
}

void conv(ll *a,ll *b){
    zeta(a);
    zeta(b);
    for(int i=0;i<1<<n;i++)a[i]*=b[i];
    mobius(a);
    for(int i=0;i<1<<n;i++)a[i]=min(a[i],1LL);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> l >> n >> t;
    t/=2;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
    }
    calc(dp[0],1,1);
    calc(dp[1],1,l);
    calc(dp[2],l,1);
    calc(dp[3],l,l);
    conv(dp[0],dp[1]);
    conv(dp[2],dp[3]);
    conv(dp[0],dp[2]);
    cout << (dp[0][(1<<n)-1]?"Yes":"No");
}