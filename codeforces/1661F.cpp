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
    cin >> n;
    vector<ll> a(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    ll m;
    cin >> m;
    vector<ll> b(n);
    for(int i=0;i<n;i++){
        b[i]=a[i+1]-a[i];
    }
    auto cost=[&](ll gap,ll t){
        t++;
        ll val=gap/t;
        return t*val*val+(gap%t)*(2*val+1);
    };
    auto calc=[&](ll lambda)->pair<ll,ll> {
        ll res=0,cnt=0;
        for(auto x:b){
            ll l=0,r=x-1;
            while(l<r){
                ll mid=(l+r+1)/2;
                if(cost(x,mid-1)-cost(x,mid)>=lambda){
                    l=mid;
                }else{
                    r=mid-1;
                }
            }
            res+=cost(x,l);
            cnt+=l;
        }
        return make_pair(res,cnt);
    };
    ll l=0,r=1e18;
    while(l<r){
        ll mid=(l+r+1)/2;
        if(calc(mid).first<=m)l=mid;
        else r=mid-1;
    }
    auto [val,ans]=calc(l);
    ans-=(m-val)/l;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}