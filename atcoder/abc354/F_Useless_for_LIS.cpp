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
    vi a(n),dpl(n),dpr(n);
    for(auto &x:a)cin >> x;
    vi v;
    for(int i=0;i<n;i++){
        auto it=lower_bound(all(v),a[i]);
        dpl[i]=it-v.begin();
        if(it==v.end())v.emplace_back(a[i]);
        else *it=a[i];
    }
    int lis=sz(v);
    v.clear();
    for(int i=n-1;i>=0;i--){
        auto it=lower_bound(all(v),-a[i]);
        dpr[i]=it-v.begin();
        if(it==v.end())v.emplace_back(-a[i]);
        else *it=-a[i];
    }
    vi ans;
    for(int i=0;i<n;i++)if(dpl[i]+dpr[i]+1==lis)ans.emplace_back(i+1);
    cout << sz(ans) << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}