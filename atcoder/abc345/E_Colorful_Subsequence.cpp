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

using pllll = pair<pll,pll>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vi c(n),v(n);
    for(int i=0;i<n;i++)cin >> c[i] >> v[i];
    ll sum=accumulate(all(v),0LL);
    vector<pllll> dp(k+1,pllll(pll(LINF,0),pll(LINF,0)));
    dp[0].first=pll(0,0);
    auto upd=[&](pllll &x,pll v){
        if(v.second==x.first.second)x.first=min(x.first,v);
        else x.second=min(x.second,v);
        if(x.second<x.first)swap(x.first,x.second);
    };
    for(int i=0;i<n;i++){
        vector<pllll> ndp(k+1,pllll(pll(LINF,0),pll(LINF,0)));
        for(int j=0;j<=k;j++){
            if(dp[j].first.second!=c[i]){
                upd(ndp[j],pll(dp[j].first.first,c[i]));
            }
            if(dp[j].second.second!=c[i]){
                upd(ndp[j],pll(dp[j].second.first,c[i]));
            }
        }
        for(int j=1;j<=k;j++){
            upd(ndp[j],pll(dp[j-1].first.first+v[i],dp[j-1].first.second));
            upd(ndp[j],pll(dp[j-1].second.first+v[i],dp[j-1].second.second));
        }
        swap(dp,ndp);
    }
    cout << max(-1LL,sum-dp[k].first.first);
}