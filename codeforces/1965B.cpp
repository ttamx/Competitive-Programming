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
    int n,k;
    cin >> n >> k;
    vi ans;
    int mx=0;
    for(int i=1;(i*2)-1<k;i<<=1){
        ans.emplace_back(i);
        mx=i*2-1;
    }
    if(k-mx>1)ans.emplace_back(k-mx-1);
    ans.emplace_back(k+1);
    ans.emplace_back(2*k);
    ans.emplace_back(3*k);
    for(int i=4*k;i-1<=n;i<<=1)ans.emplace_back(i);
    cout << sz(ans) << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}