#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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
    vi a(n);
    for(auto &x:a)cin >> x;
    ll ans=0,sum=0;
    deque<pll> dq;
    for(auto x:a){
        ll cnt=0;
        while(!dq.empty()&&dq.back().first>x){
            auto [v,c]=dq.back();
            dq.pop_back();
            sum-=v*c;
            cnt+=c;
        }
        if(cnt){
            dq.emplace_back(x,cnt);
            sum+=x*cnt;
        }
        dq.emplace_back(n,1);
        sum+=n;
    }
    ans=sum;
    for(auto x:a){
        auto &[v,c]=dq.front();
        sum-=v;
        if(--c==0)dq.pop_front();
        ll cnt=0;
        while(!dq.empty()&&dq.back().first>x){
            auto [v,c]=dq.back();
            dq.pop_back();
            sum-=v*c;
            cnt+=c;
        }
        if(cnt){
            dq.emplace_back(x,cnt);
            sum+=x*cnt;
        }
        dq.emplace_back(n,1);
        sum+=n;
        ans=max(ans,sum);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}