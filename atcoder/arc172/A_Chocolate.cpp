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
    int h,w,n;
    cin >> h >> w >> n;
    vl req(30);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        req[x]++;
    }
    vl cnt(30);
    function<void(int,int,int)> solve=[&](int h,int w,int s){
        if(s<0||h==0||w==0)return;
        ll hh=h>>s,ww=w>>s;
        cnt[s]+=hh*ww;
        solve(h-(hh<<s),w,s-1);
        solve(hh<<s,w-(ww<<s),s-1);
    };
    solve(h,w,25);
    for(int i=25;i>=0;i--){
        if(cnt[i]<req[i])return void(cout << "No\n");
        cnt[i]-=req[i];
        if(i)cnt[i-1]+=cnt[i]<<2;
    }
    cout << "Yes\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    // cin >> t;
    while(t--)runcase();
}