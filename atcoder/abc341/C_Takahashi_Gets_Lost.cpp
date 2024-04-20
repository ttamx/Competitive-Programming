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

const int N=505;

using BS = bitset<N>;
using VBS = vector<BS>;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    string s;
    cin >> s;
    VBS filter(n+2);
    for(int i=1;i<=n;i++){
        string st;
        cin >> st;
        for(int j=1;j<=m;j++)filter[i][j]=st[j-1]=='.';
    }
    auto dp=filter;
    for(auto c:s){
        auto ndp=filter;
        if(c=='L'){
            for(int i=1;i<=n;i++)ndp[i]&=dp[i]>>1;
        }else if(c=='R'){
            for(int i=1;i<=n;i++)ndp[i]&=dp[i]<<1;
        }else if(c=='U'){
            for(int i=1;i<=n;i++)ndp[i]&=dp[i+1];
        }else if(c=='D'){
            for(int i=1;i<=n;i++)ndp[i]&=dp[i-1];
        }
        swap(dp,ndp);
    }
    int ans=0;
    for(int i=1;i<=n;i++)ans+=dp[i].count();
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    // cin >> t;
    while(t--)runcase();
}