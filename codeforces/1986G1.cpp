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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

using uint = unsigned int;

const int N=5e5+5;

int a[N],b[N];

void runcase(){
    int n;
    cin >> n;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int i=0;i<n;i++){
        int g=gcd(a[i],i+1);
        a[i]/=g;
        b[i]=(i+1)/g;
    }
    map<ll,int> mp;
    ll ans=0;
    for(int i=0;i<n;i++){
        vector<int> f;
        for(int x=1;x*x<=a[i];x++){
            if(a[i]%x==0){
                f.emplace_back(x);
                if(x*x!=a[i])f.emplace_back(a[i]/x);
            }
        }
        for(auto x:f){
            auto it=mp.find(ll(x)<<19|b[i]);
            if(it!=mp.end())ans+=it->second;
        }
        for(auto x:f){
            mp[ll(b[i])<<19|x]++;
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