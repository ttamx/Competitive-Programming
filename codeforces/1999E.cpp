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

const int N=2e5+5;

ll dp[N];

void runcase(){
    int l,r;
    cin >> l >> r;
    cout << dp[r]+dp[l]-2*dp[l-1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    dp[0]=0;
    for(int i=1;i<N;i++)dp[i]=dp[i/3]+1;
    for(int i=1;i<N;i++)dp[i]+=dp[i-1];
    int t(1);
    cin >> t;
    while(t--)runcase();
}