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

struct DP{
    bool ok;
    char c;
    int pre;
    DP():ok(false),c('0'),pre(-1){}
    DP(char _c,int _pre):ok(true),c(_c),pre(_pre){}
};

void runcase(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    reverse(s.begin(),s.end());
    vector<int> cnt(k+1);
    for(int i=0;i<n;i++){
        string t;
        cin >> t;
        reverse(t.begin(),t.end());
        for(int i=1;i<=k;i++)cnt[i]+=(t[i-1]=='1');
    }
    vector dp(k+1,vector<DP>(n+1,DP()));
    dp[0][0].ok=true;
    for(int i=1;i<=k;i++){
        int tar=(s[i-1]=='1');
        for(int j=0;j<=n;j++)if(dp[i-1][j].ok){
            {
                int val=cnt[i]+j;
                int d=val&1;
                int c=val>>1;
                if(d==tar){
                    dp[i][c]=DP('0',j);
                }
            }
            {
                int val=(n-cnt[i])+j;
                int d=val&1;
                int c=val>>1;
                if(d==tar){
                    dp[i][c]=DP('1',j);
                }
            }
        }
    }
    if(dp[k][0].ok){
        int j=0;
        for(int i=k;i>=1;i--){
            cout << dp[i][j].c;
            j=dp[i][j].pre;
        }
        cout << "\n";
    }else{
        cout << -1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}