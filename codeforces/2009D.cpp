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
    vector<pair<int,int>> a(n);
    map<pair<int,int>,int> cnt;
    for(auto &[x,y]:a){
        cin >> x >> y;
        cnt[{x,y}]++;
    }
    sort(a.begin(),a.end());
    ll ans=0;
    for(int i=1;i<n;i++){
        if(a[i-1].first==a[i].first){
            ans+=n-2;
        }
    }
    for(auto [x,y]:a){
        if(cnt.count({x-1,y^1})&&cnt.count({x+1,y^1})){
            ans++;
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