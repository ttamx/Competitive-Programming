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
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    for(int i=0;i<n-1;i++)a[i+1]+=a[i];
    ll mx=0;
    pair<ll,ll> ans(0,0);
    reverse(a.begin(),a.end());
    a.emplace_back(0);
    for(auto x:a){
        ans=max(ans,{x+mx,x});
        mx=max(mx,a[0]-x);
    }
    cout << ans.second << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}