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
    int n,m,x;
    cin >> n >> m >> x;
    vi dp(n);
    dp[x-1]=1;
    for(int i=0;i<m;i++){
        int r;
        char c;
        cin >> r >> c;
        vi ndp(n);
        if(c=='0'||c=='?'){
            for(int i=0;i<n;i++)if(dp[i])ndp[(i+r)%n]=1;
        }
        if(c=='1'||c=='?'){
            for(int i=0;i<n;i++)if(dp[i])ndp[(i+n-r)%n]=1;
        }
        swap(dp,ndp);
    }
    cout << accumulate(all(dp),0) << "\n";
    for(int i=0;i<n;i++)if(dp[i])cout << i+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}