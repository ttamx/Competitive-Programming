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
    auto ask=[&](int a,int b){
        cout << "? " << a+1 << " " << b+1 << endl;
        int res;
        cin >> res;
        return res-1;
    };
    int n;
    cin >> n;
    vector<pair<int,int>> ans;
    vector<bool> done(n);
    function<void(int,int)> rec=[&](int l,int r){
        if(done[r])return;
        int m=ask(l,r);
        if(m==l){
            ans.emplace_back(l,r);
            done[r]=true;
            return;
        }
        rec(l,m);
        rec(m,r);
    };
    for(int i=1;i<n;i++)rec(0,i);
    cout << "! ";
    for(auto [u,v]:ans)cout << u+1 << " " << v+1 << " ";
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}