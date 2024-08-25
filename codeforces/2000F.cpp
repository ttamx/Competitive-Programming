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

const int N=105;

int dp[N][N][2*N];
bool vis[N][N][2*N];

int calc(int i,int j,int k){
    if(k==0)return 0;
    if(i==0||j==0||k>i+j)return INF;
    if(i==1&&j==1)return 1;
    if(vis[i][j][k])return dp[i][j][k];
    vis[i][j][k]=true;
    return dp[i][j][k]=min(calc(i-1,j,k-1)+j,calc(i,j-1,k-1)+i);
}

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> dp(k+1,INF);
    dp[0]=0;
    for(int i=0;i<n;i++){
        int a,b;
        cin >> a >> b;
        auto ndp=dp;
        for(int i=0;i<=k;i++){
            for(int j=0;j<=min(a+b,i);j++){
                ndp[i]=min(ndp[i],dp[i-j]+calc(a,b,j));
            }
        }
        swap(dp,ndp);
    }
    cout << (dp[k]<INF?dp[k]:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}