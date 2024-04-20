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
    int n;
    cin >> n;
    int m=1<<n;
    vector<string> s(n),t(n);
    map<string,int> ms,mt;
    for(int i=0;i<n;i++){
        cin >> s[i] >> t[i];
        ms[s[i]],mt[t[i]];
    }
    int cnt=0;
    for(auto &[x,y]:ms)y=cnt++;
    cnt=0;
    for(auto &[x,y]:mt)y=cnt++;
    vi a(n),b(n);
    for(int i=0;i<n;i++)a[i]=ms[s[i]];
    for(int i=0;i<n;i++)b[i]=mt[t[i]];
    int ans=n-1;
    vector<vi> dp(m,vi(n));
    for(int mask=1;mask<m;mask++){
        int pc=__builtin_popcount(mask);
        for(int i=0;i<n;i++)if(mask>>i&1){
            if(pc==1){
                dp[mask][i]=true;
                continue;
            }
            int mask2=mask^(1<<i);
            for(int j=0;j<n;j++)if(mask2>>j&1){
                if(!dp[mask2][j])continue;
                if(a[i]==a[j]||b[i]==b[j]){
                    dp[mask][i]=true;
                    break;
                }
            }
            if(dp[mask][i])ans=min(ans,n-pc);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}