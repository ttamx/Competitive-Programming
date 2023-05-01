#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=350;

int n,q,k;
int a[N],dp[K][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    k=sqrt(n)+1;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=k;i++)for(int j=1;j<=n;j++)dp[i][j]=a[j]+(j>=i?dp[i][j-i]:0);
    while(q--){
        int l,m,r;
        cin >> l >> m >> r;
        r-=(r-l)%m;
        if(m<=k){
            cout << dp[m][r]-dp[m][max(l-m,0)] << ' ';
        }else{
            int res=0;
            for(int i=l;i<=r;i+=m)res+=a[i];
            cout << res << ' ';
        }
    }
}