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
    if(k&1)return void(cout << "No\n");
    k/=2;
    vector<int> a(n);
    iota(all(a),1);
    for(int l=0,r=n-1;l<r;l++){
        if(k>=r-l){
            k-=r-l;
            swap(a[l],a[r]);
            r--;
        }
    }
    if(k>0)return void(cout << "No\n");
    cout << "Yes\n";
    for(auto x:a)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}