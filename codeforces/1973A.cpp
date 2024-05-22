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
    multiset<int> ms;
    int ok=1;
    for(int i=0;i<3;i++){
        int x;
        cin >> x;
        if(x)ms.emplace(x);
        ok^=x&1;
    }
    if(!ok)return void(cout << "-1\n");
    int ans=0;
    while(sz(ms)>1){
        int l=*ms.begin();
        ms.erase(ms.begin());
        int r=*prev(ms.end());
        ms.erase(prev(ms.end()));
        ans++;
        if(--l)ms.emplace(l);
        if(--r)ms.emplace(r);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}