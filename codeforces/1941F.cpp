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
    vl a(n),d(m),f(k);
    for(auto &x:a)cin >> x;
    for(auto &x:d)cin >> x;
    for(auto &x:f)cin >> x;
    vector<pll> b;
    for(int i=1;i<n;i++)b.emplace_back(a[i]-a[i-1],i);
    sort(rall(b));
    auto [ans,id]=b[0];
    sort(all(d));
    sort(all(f));
    ll med=(a[id]+a[id-1])/2;
    for(auto x:d){
        auto it=upper_bound(all(f),med-x);
        if(it!=f.begin()){
            ll val=x+*prev(it);
            if(val>a[id-1]){
                ans=min(ans,max(val-a[id-1],a[id]-val));
            }
        }
        it=lower_bound(all(f),med-x);
        if(it!=f.end()){
            ll val=x+*it;
            if(val<a[id]){
                ans=min(ans,max(val-a[id-1],a[id]-val));
            }
        }
    }
    if(n>2)ans=max(ans,b[1].first);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}