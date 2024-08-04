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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    ll ans=accumulate(a.begin(),a.end(),0ll);
    using T = tuple<ll,ll,ll>;
    priority_queue<T,vector<T>,greater<T>> pq;
    for(auto x:a)pq.emplace(x*3,x,3);
    for(int i=2;i<n;i++){
        auto [s,x,d]=pq.top();
        pq.pop();
        ans+=s;
        pq.emplace(x*(d+2),x,d+2);
    }
    cout << ans << "\n";
}