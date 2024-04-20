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
    int n,m,k;
    cin >> n >> m >> k;
    map<int,int> b,c;
    vi a(n);
    for(auto &x:a)cin >> x;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        b[x]++;
    }
    int cnt=0;
    auto work=[&](int x,int v){
        cnt-=min(c[x],b[x]);
        c[x]+=v;
        cnt+=min(c[x],b[x]);
    };
    for(int i=0;i<m-1;i++)work(a[i],1);
    int ans=0;
    for(int i=m-1;i<n;i++){
        work(a[i],1);
        if(cnt>=k)ans++;
        work(a[i-m+1],-1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}