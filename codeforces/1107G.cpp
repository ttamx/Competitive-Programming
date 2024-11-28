#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n;
    ll a;
    cin >> n >> a;
    vector<ll> d(n),c(n);
    for(int i=0;i<n;i++){
        cin >> d[i] >> c[i];
    }
    vector<int> p(n);
    vector<ll> sum(n),pre(n),suf(n),dp(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=u==p[u]?u:fp(p[u]);
    };
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        ll nsum=sum[u]+sum[v];
        ll npre=max(pre[u],sum[u]+pre[v]);
        ll nsuf=max(suf[v],sum[v]+suf[u]);
        ll ndp=max({dp[u],dp[u],suf[u]+pre[v]});
        sum[u]=nsum;
        pre[u]=npre;
        suf[u]=nsuf;
        dp[u]=ndp;
        p[v]=u;
    };
    vector<pair<ll,int>> event;
    for(int i=0;i+1<n;i++){
        event.emplace_back((d[i+1]-d[i])*(d[i+1]-d[i]),i);
    }
    sort(event.begin(),event.end());
    ll ans=0;
    for(int i=0;i<n;i++){
        ll val=a-c[i];
        ans=max(ans,val);
        sum[i]=val;
        pre[i]=suf[i]=dp[i]=max(val,0LL);
    }
    for(auto [w,i]:event){
        uni(i,i+1);
        ans=max(ans,dp[fp(i)]-w);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}