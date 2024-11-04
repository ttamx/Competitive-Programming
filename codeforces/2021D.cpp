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

struct Info{
    ll val,mx,pre;
    Info(ll _val,ll _mx,ll _pre):val(_val),mx(_mx),pre(_pre){}
    Info(ll _val,ll _mx):val(_val),mx(_mx),pre(_mx){}
};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> a(n,vector<ll>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<ll> dpl(m),dpr(m);
    {
        ll sum=0,mn=0;
        for(int i=0;i<m;i++){
            sum+=a[0][i];
            dpr[i]=sum-mn;
            mn=min(mn,sum);
        }
    }
    {
        ll sum=0,mn=0;
        for(int i=m-1;i>=0;i--){
            sum+=a[0][i];
            dpl[i]=sum-mn;
            mn=min(mn,sum);
        }
    }
    for(int ii=1;ii<n;ii++){
        auto v=a[ii];
        auto qs=v;
        for(int i=1;i<m;i++){
            qs[i]+=qs[i-1];
        }
        vector<ll> ndpl(m,-LINF),ndpr(m,-LINF);
        {
            ll mx1=0,mx2=-LINF;
            for(int i=1;i<m;i++){
                mx2=max(mx2,max(dpr[i-1],dpl[i])+mx1);
                mx1=max(mx1,-qs[i-1]);
                ndpr[i]=mx2+qs[i];
            }
        }
        {
            ll mx1=-LINF,mx2=-LINF;
            for(int i=m-2;i>=0;i--){
                mx1=max(mx1,qs[i+1]);
                mx2=max(mx2,max(dpl[i+1],dpr[i])+mx1);
                ndpl[i]=mx2-(i>=1?qs[i-1]:0LL);
            }
        }
        swap(dpl,ndpl);
        swap(dpr,ndpr);
    }
    ll ans=-LINF;
    for(int i=0;i<m;i++){
        ans=max(ans,dpl[i]);
        ans=max(ans,dpr[i]);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}