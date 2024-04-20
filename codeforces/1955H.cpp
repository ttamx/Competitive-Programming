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
    int n,m,k;
    cin >> n >> m >> k;
    vl pw(14);
    pw[0]=1;
    for(int i=1;i<14;i++)pw[i]=pw[i-1]*3;
    vector<string> s(n);
    for(auto &x:s)cin >> x;
    vector<vl> a(k,vl(13));
    ll ans=0;
    for(int id=0;id<k;id++){
        int x,y;
        ll p;
        cin >> x >> y >> p;
        x--,y--;
        if(s[x][y]=='#')ans+=p;
        for(int r=0;r<13;r++){
            a[id][r]=-pw[r+1];
            for(int i=0;i<n;i++)for(int j=0;j<m;j++){
                if(s[i][j]=='#'&&(i-x)*(i-x)+(j-y)*(j-y)<=(r+1)*(r+1)){
                    a[id][r]+=p;
                }
            }
            if(s[x][y]=='#')a[id][r]-=p;
            a[id][r]=max(a[id][r],0LL);
        }
    }
    vl dp(1<<13);
    for(int i=0;i<k;i++){
        for(int mask=(1<<13)-1;mask>0;mask--){
            for(int j=0;j<13;j++)if(mask>>j&1){
                dp[mask]=max(dp[mask],dp[mask^(1<<j)]+a[i][j]);
            }
        }
    }
    cout << ans+dp.back() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}