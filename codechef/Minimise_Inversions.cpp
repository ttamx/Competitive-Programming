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
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a;
    for(auto x:s)a.emplace_back(x=='1');
    vector dp(n,vector<int>(n));
    for(int l=0;l<n;l++){
        int cnt=0,cur=0;
        for(int r=l;r<n;r++){
            if(a[r]==0)cur+=cnt;
            else cnt++;
            dp[l][r]=cur;
        }
    }
    int cnt=0;
    int ans=INF;
    for(int l=0;l<n;l++){
        int cnt2=cnt;
        for(int r=n-1;r>=l;r--){
            if(cnt2<=k)ans=min(ans,dp[l][r]);
            if(a[r]==0)cnt2++;
        }
        if(a[l]==1)cnt++;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}