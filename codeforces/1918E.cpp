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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    cin >> n;
    auto ask=[&](int i){
        cout << "? " << i+1 << "\n" << flush;
        char c;
        cin >> c;
        if(c=='<')return -1;
        if(c=='>')return 1;
        return 0;
    };
    vector<pii> ran;
    vi a(n);
    iota(all(a),0);
    function<void(int,int)> solve=[&](int l,int r){
        if(l>=r)return;
        int sz=r-l+1;
        int p=rng()%sz;
        p+=p<0?l+sz:l;
        swap(a[p],a[r]);
        p=a[r];
        while(ask(p)!=0);
        int m=l-1;
        for(int j=l;j<r;j++){
            if(ask(a[j])<0)swap(a[++m],a[j]);
            ask(p);
        }
        swap(a[++m],a[r]);
        solve(l,m-1);
        solve(m+1,r);
    };
    solve(0,n-1);
    vi ans(n);
    for(int i=0;i<n;i++)ans[a[i]]=i;
    cout << "!";
    for(auto x:ans)cout << " " << x+1;
    cout << "\n";
    cout << flush;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}