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
    int n,q;
    cin >> n >> q;
    vi a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    map<int,vector<int>> mp;
    mp[0].emplace_back(0);
    for(int i=1;i<=n;i++){
        a[i]^=a[i-1];
        mp[a[i]].emplace_back(i);
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        int x=a[l-1],y=a[r];
        if(x==y){
            cout << "YES\n";
            continue;
        }
        auto it1=lower_bound(all(mp[y]),l);
        auto it2=lower_bound(all(mp[x]),*it1);
        cout << ((it2!=mp[x].end()&&*it2<r)?"YES":"NO") << "\n";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}