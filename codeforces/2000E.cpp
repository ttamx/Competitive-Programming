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
    int n,m,k,w;
    cin >> n >> m >> k >> w;
    vector<ll> a(w);
    for(auto &x:a)cin >> x;
    vector<vector<int>> b(n+1,vector<int>(m+1));
    for(int i=0;i+k<=n;i++){
        for(int j=0;j+k<=m;j++){
            b[i][j]++;
            b[i][j+k]--;
            b[i+k][j]--;
            b[i+k][j+k]++;
        }
    }
    vector<ll> c;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i>0)b[i][j]+=b[i-1][j];
            if(j>0)b[i][j]+=b[i][j-1];
            if(i>0&&j>0)b[i][j]-=b[i-1][j-1];
            c.emplace_back(b[i][j]);
        }
    }
    sort(a.rbegin(),a.rend());
    sort(c.rbegin(),c.rend());
    ll ans=0;
    for(int i=0;i<w;i++){
        ans+=a[i]*c[i];
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}