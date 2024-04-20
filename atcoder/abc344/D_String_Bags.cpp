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

int dp[N][N];

int n;
string t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t >> n;
    int m=t.size();
    for(int j=1;j<=m;j++)dp[0][j]=INF;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)dp[i][j]=dp[i-1][j];
        int k;
        cin >> k;
        while(k--){
            string s;
            cin >> s;
            int l=s.size();
            for(int j=l;j<=m;j++)if(t.substr(j-l,l)==s){
                dp[i][j]=min(dp[i][j],dp[i-1][j-l]+1);
            }
        }
    }
    cout << (dp[n][m]==INF?-1:dp[n][m]);
}