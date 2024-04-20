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
    ll k;
    cin >> n >> k;
    deque<ll> a(n);
    for(auto &x:a)cin >> x;
    int ans=0;
    while(sz(a)>1&&k>1){
        ll d=min({k/2,a.front(),a.back()});
        a.front()-=d;
        a.back()-=d;
        k-=2*d;
        if(a.front()==0){
            a.pop_front();
            ans++;
        }
        if(a.back()==0){
            a.pop_back();
            ans++;
        }
    }
    if(sz(a)==1&&k>=a[0])ans++;
    else if(sz(a)>1&&(k+1)/2>=a[0])ans++;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}