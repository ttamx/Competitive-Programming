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
    vi a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    sort(all(a));
    sort(all(b));
    a.erase(unique(all(a)),a.end());
    b.erase(unique(all(b)),b.end());
    while(!a.empty()&&a.back()>k)a.pop_back();
    while(!b.empty()&&b.back()>k)b.pop_back();
    vi c(k);
    for(auto x:a)c[x-1]|=1;
    for(auto x:b)c[x-1]|=2;
    int ca=0,cb=0;
    for(auto x:c){
        if(x==0)return void(cout <<"NO\n");
        if(x==1&&++ca>k/2)return void(cout << "NO\n");
        if(x==2&&++cb>k/2)return void(cout << "NO\n");
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}