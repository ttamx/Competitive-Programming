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

const int N=205;

bool vis[N][N][N];
int dp[N][N][N];

int solve(int a,int b,int c){
    if(vis[a][b][c])return dp[a][b][c];
    vis[a][b][c]=true;
    int &x=dp[a][b][c];
    if(a)x=max(x,solve(a-1,b,c));
    if(b)x=max(x,solve(a,b-1,c));
    if(c)x=max(x,solve(a,b,c-1));
    int cur=0;
    if(a&1)cur^=1;
    if(b&1)cur^=2;
    if(c&1)cur^=3;
    if(!cur)x++;
    return x;
}

void runcase(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << solve(a,b,c)+d/2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vis[0][0][0]=true;
    int t(1);
    cin >> t;
    while(t--)runcase();
}