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
    vl a(n);
    for(auto &x:a)cin >> x;
    ll ans=(n-1)*max(a[0],a[n-1]);
    vl dpl(n,LINF),dpr(n,LINF);
    ll val=a[0],pos=0,cur=0;
    dpl[0]=0;
    for(int i=1;i<n;i++)if(a[i]<=val){
        cur+=(i-pos)*val;
        val=a[i],pos=i;
        dpl[i]=cur;
    }
    val=a[n-1],pos=n-1,cur=0;
    dpr[n-1]=0;
    for(int i=n-2;i>=0;i--)if(a[i]<=val){
        cur+=(pos-i)*val;
        val=a[i],pos=i;
        dpr[i]=cur;
    }
    for(int i=0;i<n;i++)ans=min(ans,dpl[i]+dpr[i]);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}