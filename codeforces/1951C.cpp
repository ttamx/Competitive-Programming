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
    vi a(n);
    for(auto &x:a)cin >> x;
    vector<pii> b;
    for(int i=0;i<n;i++)b.emplace_back(a[i],i);
    sort(all(b));
    int cnt=(k-1)/m+1;
    int rem=k%m;
    b.resize(cnt);
    sort(all(b),[&](pii x,pii y){
        return x.second<y.second;
    });
    if(rem==0){
        ll ans=0;
        for(int i=0;i<cnt;i++)ans+=1LL*m*(b[i].first+1LL*i*m);
        cout << ans << "\n";
    }else{
        vl pre(cnt+2),suf(cnt+2);
        for(int i=1;i<=cnt;i++){
            pre[i]=pre[i-1]+1LL*m*(b[i-1].first+1LL*(i-1)*m);
        }
        for(int i=cnt;i>=1;i--){
            suf[i]=suf[i+1]+1LL*m*(b[i-1].first+1LL*(k-((cnt-i+1)*m)));
        }
        ll ans=LINF;
        for(int i=1;i<=cnt;i++){
            ans=min(ans,pre[i-1]+suf[i+1]+1LL*rem*(b[i-1].first+1LL*(i-1)*m));
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}