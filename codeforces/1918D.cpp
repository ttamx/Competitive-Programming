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
    vl a(n+2),qs(n+2);
    for(int i=2;i<=n+1;i++)cin >> a[i];
    for(int i=2;i<=n+1;i++)qs[i]=a[i]+qs[i-1];
    ll l=*max_element(all(a)),r=qs[n+1];
    auto check=[&](ll m){
        vl dp(n+2);
        deque<int> dq;
        dq.emplace_back(1);
        for(int i=2,j=2;i<=n+1;i++){
            while(!dq.empty()&&qs[i]-qs[dq.front()]>m)dq.pop_front();
            dp[i]=max(qs[i]-qs[dq.front()]+dp[dq.front()-1],dp[i-1]);
            while(!dq.empty()&&dp[dq.back()-1]-qs[dq.back()]<dp[i-1]-qs[i])dq.pop_back();
            dq.emplace_back(i);
        }
        return qs[n+1]-dp[n+1]<=m;
    };
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}