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
    vi a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    multiset<int> ms;
    map<int,bool> good;
    for(auto x:b)good[x]=true;
    for(int i=0;i<n;i++)if(a[i]!=b[i]){
        ms.emplace(b[i]);
    }
    int m;
    cin >> m;
    vi d(m);
    for(auto &x:d)cin >> x;
    reverse(all(d));
    bool ok=false;
    for(auto x:d){
        auto it=ms.find(x);
        if(it==ms.end()){
            if(good[x])ok=true;
            if(ok)continue;
            return void(cout << "NO\n");
        }
        ok=true;
        ms.erase(it);
    }
    cout << (ms.empty()?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}