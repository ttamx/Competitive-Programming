#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
const int MOD=1000000007;
// const int MOD=998224353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

void runcase(){
    int n;
    cin >> n;
    vi a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vi> mex(n+2,vi(n+2));
    vector<vector<pii>> good(n+2);
    for(int l=n;l>=1;l--){
        vi cnt(n+2);
        int val=0;
        for(int r=l;r<=n;r++){
            cnt[a[r]]++;
            while(cnt[val])val++;
            mex[l][r]=val;
            if(l==r||(mex[l][r]!=mex[l+1][r]&&mex[l][r]!=mex[l][r-1]))good[l].emplace_back(r,mex[l][r]);
        }
    }
    vector<vector<bool>> dp(n+2,vector<bool>(2*n+2));
    dp[0][0]=true;
    for(int i=0;i<n;i++)for(int j=0;j<2*n;j++)if(dp[i][j]){
        dp[i+1][j]=true;
        for(auto [k,x]:good[i+1])dp[k][j^x]=true;
    }
    for(int i=2*n-1;i>=0;i--)if(dp[n][i])return void(cout << i << "\n");
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}