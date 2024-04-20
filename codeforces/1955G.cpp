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
    int n,m;
    cin >> n >> m;
    vector<vi> a(n,vi(m));
    for(auto &x:a)for(auto &y:x)cin >> y;
    vi v;
    int val=a[0][0];
    int mx=0;
    for(int d=1;d*d<=val;d++)if(val%d==0){
        mx=d;
        int x=val/d;
        vector<vector<bool>> dp(n,vector<bool>(m));
        dp[0][0]=true;
        for(int i=0;i<n;i++)for(int j=0;j<m;j++){
            if(a[i][j]%x)dp[i][j]=0;
            if(dp[i][j]){
                if(i+1<n)dp[i+1][j]=true;
                if(j+1<m)dp[i][j+1]=true;
            }
        }
        if(dp[n-1][m-1])return void(cout << x << "\n");
    }
    for(int x=mx;x>=1;x--)if(val%x==0){
        vector<vector<bool>> dp(n,vector<bool>(m));
        dp[0][0]=true;
        for(int i=0;i<n;i++)for(int j=0;j<m;j++){
            if(a[i][j]%x)dp[i][j]=0;
            if(dp[i][j]){
                if(i+1<n)dp[i+1][j]=true;
                if(j+1<m)dp[i][j+1]=true;
            }
        }
        if(dp[n-1][m-1])return void(cout << x << "\n");
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}