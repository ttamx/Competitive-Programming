#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n,x,y;
    cin >> n >> x >> y;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++)cin >> a[i] >> b[i];
    vector<vector<int>> dp(n+1,vector<int>(x+1,INF));
    dp[0][0]=0;
    for(int i=0;i<n;i++){
        auto ndp=dp;
        for(int j=0;j<n;j++){
            for(int k=0;k+a[i]<=x;k++){
                ndp[j+1][k+a[i]]=min(ndp[j+1][k+a[i]],dp[j][k]+b[i]);
            }
        }
        swap(dp,ndp);
    }
    int ans=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<=x;j++){
            if(dp[i][j]<=y){
                ans=i+1;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}