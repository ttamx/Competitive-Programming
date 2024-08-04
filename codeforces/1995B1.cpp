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
    ll m;
    cin >> n >> m;
    map<ll,ll> cnt;
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        cnt[x]++;
    }
    vector<pair<ll,ll>> a;
    for(auto [x,y]:cnt)a.emplace_back(x,y);
    n=a.size();
    ll ans=0;
    for(auto [x,y]:a){
        ll t=min(m/x,y);
        ans=max(ans,x*t);
    }
    for(int i=1;i<n;i++){
        if(a[i-1].first+1!=a[i].first)continue;
        ll t=min(m/a[i-1].first,a[i-1].second+a[i].second);
        auto check=[&](ll x){
           return a[i-1].first*x+max(0LL,x-a[i-1].second)<=m;
        };
        ll l=0,r=t;
        while(l<r){
            ll mid=(l+r+1)/2;
            if(check(mid))l=mid;
            else r=mid-1;
        }
        if(check(l)){
            ans=max(ans,a[i-1].first*l+min(a[i].second,l));
        }
    }
    cout << min(ans,m) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}