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

int n;
string s;
ll c[N];
ll pre[N][2],suf[N][2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    cin >> s;
    for(int i=1;i<=n;i++)cin >> c[i];
    pre[1]['1'-s[0]]=c[1];
    suf[n]['1'-s[n-1]]=c[n];
    for(int i=2;i<=n;i++){
        pre[i][0]=pre[i-1][1];
        pre[i][1]=pre[i-1][0];
        pre[i]['1'-s[i-1]]+=c[i];
    }
    for(int i=n-1;i>=1;i--){
        suf[i][0]=suf[i+1][1];
        suf[i][1]=suf[i+1][0];
        suf[i]['1'-s[i-1]]+=c[i];
    }
    ll ans=LINF;
    for(int i=2;i<=n;i++){
        ans=min(ans,pre[i-1][0]+suf[i][0]);
        ans=min(ans,pre[i-1][1]+suf[i][1]);
    }
    cout << ans << "\n";
}