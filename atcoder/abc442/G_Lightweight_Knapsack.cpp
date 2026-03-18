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
    ll c;
    cin >> n >> c;
    vector<pair<ll,ll>> a[4];
    ll tot[4]={};
    for(int i=0;i<n;i++){
        int w,v,k;
        cin >> w >> v >> k;
        a[w].emplace_back(v,k);
        tot[w]+=k;
    }
    for(int i=1;i<=3;i++)sort(a[i].rbegin(),a[i].rend());
    ll ans=0;
    auto calc1=[&](ll x,ll y){
        ll z=c-x*3-y*2;
        ll res=0;
        for(auto [v,k]:a[3]){
            ll used=min(k,x);
            res+=v*used;
            x-=used;
        }
        for(auto [v,k]:a[2]){
            ll used=min(k,y);
            res+=v*used;
            y-=used;
        }
        for(auto [v,k]:a[1]){
            ll used=min(k,z);
            res+=v*used;
            z-=used;
        }
        return res;
    };
    auto calc2=[&](ll x){
        ll l=0,r=min((c-x*3)/2,tot[2]);
        while(l<r){
            ll m=(l+r)/2;
            if(calc1(x,m+1)>calc1(x,m))l=m+1;
            else r=m;
        }
        return calc1(x,l);
    };
    for(int t=0;t<2;t++){
        ll l=0,r=min((c/3-t+2)/2-1,tot[3]);
        while(l<r){
            ll m=(l+r)/2;
            if(calc2((m+1)*2+t)>calc2(m*2+t))l=m+1;
            else r=m;
        }
        if(l<=r){
            ans=max(ans,calc2(l*2+t));
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}