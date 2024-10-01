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
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(k),b(k);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    a.insert(a.begin(),0);
    b.insert(b.begin(),0);
    while(q--){
        int x;
        cin >> x;
        int i=upper_bound(a.begin(),a.end(),x)-a.begin()-1;
        if(x==a[i]){
            cout << b[i] << " ";
        }else{
            cout << b[i]+1LL*(x-a[i])*(b[i+1]-b[i])/(a[i+1]-a[i]) << " ";
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}