#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=300;
const int V=1e5;

ll n;
int m;
int a[N+1];
ll dp[V];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        a[x]=max(a[x],y);
    }
    for(int i=1;i<=N;i++){
        int c=i-a[i];
        for(int j=i;j<V;j++){
            dp[j]=max(dp[j],dp[j-c]+a[i]);
        }
    }
    if(n<V){
        cout << n+dp[n] << "\n";
        exit(0);
    }
    ll ans=0;
    for(int i=1;i<=N;i++){
        for(int j=a[i];j<V;j++){
            ans=max(ans,dp[j]+(n-j)/(i-a[i])*a[i]);
        }
    }
    cout << n+ans << "\n";
}