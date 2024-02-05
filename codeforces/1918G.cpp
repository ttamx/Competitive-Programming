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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    auto solve=[&](vi a){
        while(sz(a)<n){
            int x=a.end()[-2],y=a.back();
            a.emplace_back(-y);
            a.emplace_back(x-y);
        }
        cout << "YES\n";
        for(auto x:a)cout << x << " ";
    };
    if(n&1){
        if(n<7)cout << "NO\n";
        else solve({1,1,-2,2,3,-4,-1});
    }else{
        solve({1,2});
    }
}