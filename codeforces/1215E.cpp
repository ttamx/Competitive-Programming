#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=400005;
const int A=20;
const int B=1<<A;
const ll INF=LLONG_MAX/2;

int n;
int a[N];
int cnt[A];
ll dp[B],cost[A][A];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        cnt[--a[i]]++;
        for(int j=0;j<A;j++)cost[a[i]][j]+=cnt[j];
    }
    for(int mask=1;mask<B;mask++)dp[mask]=INF;
    for(int mask=0;mask<B;mask++){
        for(int i=0;i<A;i++)if(!(mask>>i&1)){
            ll res=dp[mask];
            for(int j=0;j<A;j++)if(mask>>j&1)res+=cost[i][j];
            dp[mask|(1<<i)]=min(dp[mask|(1<<i)],res);
        }
    }
    cout << dp[B-1] << "\n";
}