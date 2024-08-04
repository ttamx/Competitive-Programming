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
    int m=1;
    for(int i=0;i<n;i++)m*=3;
    vector<string> a(m,string(m,'.'));
    function<void(int,int,int)> solve=[&](int k,int x,int y){
        if(k==0)return void(a[x][y]='#');
        int s=1;
        for(int i=1;i<k;i++)s*=3;
        solve(k-1,x,y);
        solve(k-1,x,y+s);
        solve(k-1,x,y+2*s);
        solve(k-1,x+s,y);
        solve(k-1,x+s,y+2*s);
        solve(k-1,x+2*s,y);
        solve(k-1,x+2*s,y+s);
        solve(k-1,x+2*s,y+2*s);
    };
    solve(n,0,0);
    for(auto x:a)cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}