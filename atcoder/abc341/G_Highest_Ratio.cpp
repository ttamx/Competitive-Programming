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
    vl a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    vd ans(n);
    deque<int> dq;
    dq.emplace_back(n);
    auto bad=[&](int x,int y,int z){
        return (a[y]-a[z])*(x-z)<=(a[x]-a[z])*(y-z);
    };
    auto calc=[&](int l,int r){
        return db(a[r]-a[l])/(r-l);
    };
    for(int i=n-1;i>=0;i--){
        while(sz(dq)>1&&bad(dq.end()[-2],dq.back(),i))dq.pop_back();
        ans[i]=calc(i,dq.back());
        dq.emplace_back(i);
    }
    cout << fixed << setprecision(8);
    for(auto x:ans)cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    // cin >> t;
    while(t--)runcase();
}