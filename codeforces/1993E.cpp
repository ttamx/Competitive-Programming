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

template<class T,class U>
bool chmin(T &a,U b){
    return b<a?a=T(b),true:false;
}

void runcase(){
    int n,m;
    cin >> n >> m;
    vector a(n+1,vector<int>(m+1));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            a[i][m]^=a[i][j];
            a[n][j]^=a[i][j];
            a[n][m]^=a[i][j];
        }
    }
    vector ans(n+1,vector<int>(m+1));
    {
        auto calc=[&](int c){
            vector cost(m+1,vector<int>(m+1));
            for(int i=0;i<=m;i++){
                for(int j=0;j<=m;j++){
                    for(int k=0;k<=n;k++){
                        if(k==c)continue;
                        cost[i][j]+=abs(a[k][i]-a[k][j]);
                    }
                }
            }
            int b=1<<(m+1);
            vector dp(b,vector<int>(m+1,INF));
            for(int mask=1;mask<b;mask++){
                if(mask==(mask&-mask)){
                    for(int i=0;i<=m;i++){
                        if(mask>>i&1){
                            dp[mask][i]=0;
                            break;
                        }
                    }
                    continue;
                }
                for(int i=0;i<=m;i++){
                    if(!(mask>>i&1))continue;
                    int mask2=mask^(1<<i);
                    for(int j=0;j<=m;j++){
                        if(!(mask2>>j&1))continue;
                        chmin(dp[mask][i],dp[mask2][j]+cost[i][j]);
                    }
                }
                if(__builtin_popcount(mask)==m){
                    for(int i=0;i<=m;i++){
                        if(mask>>i&1)continue;
                        int res=INF;
                        for(int j=0;j<=m;j++){
                            chmin(res,dp[mask][j]);
                        }
                        ans[c][i]+=res;
                        break;
                    }
                }
            }
        };
        for(int i=0;i<=n;i++)calc(i);
    }
    {
        auto calc=[&](int c){
            vector cost(n+1,vector<int>(n+1));
            for(int i=0;i<=n;i++){
                for(int j=0;j<=n;j++){
                    for(int k=0;k<=m;k++){
                        if(k==c)continue;
                        cost[i][j]+=abs(a[i][k]-a[j][k]);
                    }
                }
            }
            int b=1<<(n+1);
            vector dp(b,vector<int>(n+1,INF));
            for(int mask=1;mask<b;mask++){
                if(mask==(mask&-mask)){
                    for(int i=0;i<=n;i++){
                        if(mask>>i&1){
                            dp[mask][i]=0;
                            break;
                        }
                    }
                    continue;
                }
                for(int i=0;i<=n;i++){
                    if(!(mask>>i&1))continue;
                    int mask2=mask^(1<<i);
                    for(int j=0;j<=n;j++){
                        if(!(mask2>>j&1))continue;
                        chmin(dp[mask][i],dp[mask2][j]+cost[i][j]);
                    }
                }
                if(__builtin_popcount(mask)==n){
                    for(int i=0;i<=n;i++){
                        if(mask>>i&1)continue;
                        int res=INF;
                        for(int j=0;j<=n;j++){
                            chmin(res,dp[mask][j]);
                        }
                        ans[i][c]+=res;
                        break;
                    }
                }
            }
        };
        for(int i=0;i<=m;i++)calc(i);
    }
    int res=INF;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            chmin(res,ans[i][j]);
        }
    }
    cout << res << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}