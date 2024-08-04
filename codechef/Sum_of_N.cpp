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

const int N=1e6+5;

ll lp[N];
ll dp[N];

void runcase(){
    ll n;
    cin >> n;
    cout << dp[lp[n]]*n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        dp[i]=dp[i-1];
        if(!lp[i]){
            dp[i]+=i;
            for(int j=i;j<N;j+=i)if(!lp[j])lp[j]=i;
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}