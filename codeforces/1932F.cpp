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
    vi dp(n+2),a(n+2),cnt(n+2);
    iota(all(a),0);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        a[r]=min(a[r],l);
        cnt[l]++,cnt[r+1]--;
    }
    for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1];
    for(int i=n;i>=1;i--)a[i-1]=min(a[i-1],a[i]);
    for(int i=1;i<=n;i++){
        dp[i]=max(dp[i-1],dp[a[i]-1]+cnt[i]);
    }
    cout << dp[n] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}