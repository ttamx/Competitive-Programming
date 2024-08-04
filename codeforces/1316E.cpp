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
bool chmax(T &a,const U &b){
    return a<b?a=T(b),true:false;
}

void runcase(){
    int n,p,k;
    cin >> n >> p >> k;
    vector<int> a(n);
    vector s(n,vector<int>(p));
    for(auto &x:a)cin >> x;
    for(auto &v:s)for(auto &x:v)cin >> x;
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){return a[i]>a[j];});
    int m=1<<p;
    vector suf(n,vector<ll>(m,-LINF));
    suf[n-1][0]=0;
    for(int i=n-1;i>0;i--){
        int id=ord[i];
        suf[i-1]=suf[i];
        for(int j=0;j<m;j++){
            for(int k=0;k<p;k++)if(!(j>>k&1)){
                chmax(suf[i-1][j|(1<<k)],suf[i][j]+s[id][k]);
            }
        }
    }
    vector<ll> dp(m,-LINF);
    dp[0]=0;
    ll ans=0;
    for(int i=0;i<n;i++){
        int id=ord[i];
        vector<ll> ndp=dp;
        for(auto &x:ndp)x+=a[id];
        for(int j=0;j<m;j++){
            for(int k=0;k<p;k++)if(!(j>>k&1)){
                chmax(ndp[j|(1<<k)],dp[j]+s[id][k]);
            }
        }
        swap(dp,ndp);
        for(int j=0;j<m;j++){
            if(i+1==k+__builtin_popcount(j)){
                chmax(ans,dp[j]+suf[i][(m-1)^j]);
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}