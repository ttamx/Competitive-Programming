#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=840;

int n,x,y,q;
int p[N],t[N];
ll dp[2][K];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x >> y;
    for(int i=1;i<n;i++)cin >> p[i] >> t[i];
    for(int i=n-1;i>=1;i--){
        for(int j=0;j<K;j++){
            int nxt=(j+p[i]-1)/p[i]*p[i];
            dp[i&1][j]=dp[i&1^1][(nxt+t[i])%K]+nxt-j+t[i];
        }
    }
    cin >> q;
    while(q--){
        ll v;
        cin >> v;
        v+=x;
        cout << v+dp[1][v%K]+y << "\n";
    }
}