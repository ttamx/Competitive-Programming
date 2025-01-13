#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=3003;
const int M=6005;
const int INF=1e9;

int n;
string s;
int t[N][M];
int dp[N];

void update(int x,int i,int v){
    for(i+=n+1;i<M;i+=i&-i)t[x][i]=max(t[x][i],v);
}

int query(int x,int i){
    int res=-INF;
    for(i+=n+1;i>0;i-=i&-i)res=max(res,t[x][i]);
    return res;
}

void solve(){
    cin >> n >> s;
    for(int i=0;i<=n;i++){
        for(int j=1;j<=2*n+1;j++){
            t[i][j]=-INF;
        }
    }
    update(0,0,0);
    int cur=0;
    for(int i=1;i<=n;i++){
        cur+=(s[i-1]=='1'?1:-1);
        for(int j=i;j>=1;j--){
            dp[j]=max(query(j-1,cur-1)+1,query(j-1,n));
        }
        for(int j=1;j<=i;j++){
            update(j,cur,dp[j]);
        }
    }
    for(int i=1;i<=n;i++){
        cout << dp[i] << " \n"[i==n];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}