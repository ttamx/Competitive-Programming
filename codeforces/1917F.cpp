#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    int n,d;
    cin >> n >> d;
    vi l(n);
    for(auto &x:l)cin >> x;
    sort(l.rbegin(),l.rend());
    if(l[0]+l[1]>d)return void(cout << "No\n");
    vector<bitset<2005>> dp(d+1);
    dp[0][0]=1;
    for(auto x:l){
        for(int i=d;i>=0;i--){
            dp[i]|=dp[i]<<x;
            if(i>=x)dp[i]|=dp[i-x];
        }
    }
    if(dp[l[0]][d-l[0]])return void(cout << "Yes\n");
    for(int i=l[0];i<=d-l[0];i++)if(dp[i][d-i])return void(cout << "Yes\n");
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}