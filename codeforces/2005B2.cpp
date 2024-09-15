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
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> a(m);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    while(q--){
        int x;
        cin >> x;
        auto it=lower_bound(a.begin(),a.end(),x);
        int ans=0;
        if(it==a.end()){
            ans=n-a.back();
        }else if(it==a.begin()){
            ans=a[0]-1;
        }else{
            ans=(*it-*prev(it))/2;
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}