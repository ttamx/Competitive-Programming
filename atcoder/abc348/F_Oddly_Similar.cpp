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

const int N=2005;
const int A=1005;

using BS = bitset<N>;

int n,m,ans;
int a[N][N];
BS dp[N][A];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin >> a[i][j];
            dp[j][a[i][j]][i]=1;
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            dp[j][a[i][j]][i]=0;
        }
        BS res;
        for(int j=1;j<=m;j++){
            res^=dp[j][a[i][j]];
        }
        ans+=res.count();
    }
    cout << ans;
}