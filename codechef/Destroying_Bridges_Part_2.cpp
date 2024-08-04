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
    ll c;
    cin >> n >> c;
    vl a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin()+1,a.end());
    vl pre(n),suf(n);
    for(int i=1;i<n;i++)pre[i]=pre[i-1]+a[i];
    reverse(a.begin()+1,a.end());
    for(int i=1;i<n;i++)suf[i]=suf[i-1]+a[i];
    int ans=n;
    ll tot=accumulate(a.begin()+1,a.end(),0LL);
    for(int i=0;i<n-1;i++){
        {
            ll cost=(a[0]+pre[i])*(tot-pre[i]);
            if(cost<=c){
                ans=i+1;
                break;
            }
        }
        {
            ll cost=(a[0]+suf[i])*(tot-suf[i]);
            if(cost<=c){
                ans=i+1;
                break;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}