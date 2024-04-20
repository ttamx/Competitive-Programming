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
    deque<int> a(n);
    for(auto &x:a)cin >> x;
    auto b=a;
    auto work=[&](){
        while(sz(a)>1&&a[0]==a[1])a.pop_front();
        if(!a.empty())a.pop_front();
    };
    if(a[0]==a[n-1]){
        work();
        reverse(all(a));
        work();
    }else{
        work();
        swap(a,b);
        reverse(all(a));
        work();
    }
    cout << min(sz(a),sz(b)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}