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
    int n,l,r;
    cin >> n >> l >> r;
    vector<int> dp(n);
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    for(int i=0;i<n;i++){
        int lo=-1,hi=i-1;
        while(lo<hi){
            int m=(lo+hi+1)/2;
            if(a[i]-a[m]>=l)lo=m;
            else hi=m-1;
        }
        ll sum=a[i]-(lo>=0?a[lo]:0);
        if(l<=sum&&sum<=r)dp[i]=max(dp[i],lo>=0?dp[lo]+1:1);
        if(i+1<n)dp[i+1]=dp[i];
    }
    cout << dp[n-1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}