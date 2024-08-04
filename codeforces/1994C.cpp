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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll sum=0;
    vector<int> nxt(n);
    for(int i=0,j=0;i<n;i++){
        while(sum<=k&&j<n){
            sum+=a[j];
            j++;
        }
        if(sum>k){
            nxt[i]=j;
        }else{
            nxt[i]=-1;
        }
        sum-=a[i];
    }
    vector<int> dp(n+1);
    ll ans=0;
    for(int i=n-1;i>=0;i--){
        if(nxt[i]!=-1){
            dp[i]=dp[nxt[i]]+1;
        }
        ans+=n-i-dp[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}