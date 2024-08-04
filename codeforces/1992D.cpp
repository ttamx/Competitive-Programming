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
    int n,m,k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    s="L"+s+"L";
    vector<int> dp(n+2,INF);
    dp[0]=0;
    for(int i=1;i<=n+1;i++)if(s[i]!='C'){
        for(int j=1;j<=m;j++)if(i-j>=0&&s[i-j]=='L')dp[i]=min(dp[i],dp[i-j]);
        if(s[i-1]=='W')dp[i]=min(dp[i],dp[i-1]);
        if(s[i]=='W')dp[i]++;
    }
    cout << (dp[n+1]<=k?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}