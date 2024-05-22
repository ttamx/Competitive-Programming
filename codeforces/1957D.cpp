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
    vi a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<vector<vi>> pre(n+2,vector<vi>(30,vi(2))),suf(n+2,vector<vi>(30,vi(2)));
    vi sum(n+2);
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]^a[i];
    for(int i=0;i<30;i++)pre[0][i][0]=1;
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1];
        for(int j=0;j<30;j++)pre[i][j][sum[i]>>j&1]++;
    }
    for(int i=n;i>=1;i--){
        suf[i]=suf[i+1];
        for(int j=0;j<30;j++)suf[i][j][sum[i]>>j&1]++;
    }
    ll ans=0;
    for(int i=1;i<=n;i++){
        int p=31-__builtin_clz(a[i]);
        if(p<0)continue;
        ans+=1LL*pre[i-1][p][0]*suf[i][p][0];
        ans+=1LL*pre[i-1][p][1]*suf[i][p][1];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}