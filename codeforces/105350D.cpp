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
    ll sum=0;
    vector<ll> c;
    for(int i=0;i<n;i++){
        ll a,b;
        cin >> a >> b;
        sum+=max(a,b);
        c.emplace_back(min(a,b));
    }
    sort(c.begin(),c.end());
    sum+=c.back();
    c.pop_back();
    sum*=sum;
    for(auto x:c){
        sum+=x*x;
    }
    cout << sum << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}