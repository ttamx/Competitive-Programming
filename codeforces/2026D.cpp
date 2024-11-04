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
    vector<ll> a(n),e;
    ll val=0,sum=0;
    for(auto &x:a){
        cin >> x;
        sum+=x;
        val+=sum;
        e.emplace_back(val);
    }
    vector<ll> b(n);
    for(int i=0;i<n;i++){
        b[i]=val;
        val-=a[i]*(n-i);
    }
    auto c=b;
    for(int i=1;i<n;i++){
        c[i]+=c[i-1];
    }
    auto d=a;
    for(int i=1;i<n;i++){
        d[i]+=d[i-1];
    }
    auto query=[&](int l,int r){
        ll res=d[r];
        if(l>0)res-=d[l-1];
        return res;
    };
    vector<ll> bs;
    ll cur=0;
    for(int i=n;i>=1;i--){
        cur+=i;
        bs.emplace_back(cur);
    }
    int q;
    cin >> q;
    while(q--){
        ll l,r;
        cin >> l >> r;
        l--,r--;
        ll lb=upper_bound(bs.begin(),bs.end(),l)-bs.begin();
        ll rb=upper_bound(bs.begin(),bs.end(),r)-bs.begin();
        if(lb>0)l-=bs[lb-1];
        if(rb>0)r-=bs[rb-1];
        ll ans=0;
        if(lb<rb-1){
            ans+=c[rb-1]-c[lb];
        }
        if(lb==rb){
            l+=lb,r+=rb;
            ans+=e[r];
            if(l>0)ans-=e[l-1];
            if(lb>0)ans-=d[lb-1]*(r-l+1);
        }else{
            l+=lb,r+=rb;
            ans+=e[n-1];
            if(l>0)ans-=e[l-1];
            if(lb>0)ans-=d[lb-1]*(n-l);
            ans+=e[r];
            if(rb>0){
                ans-=e[rb-1];
                ans-=d[rb-1]*(r-rb+1);
            }
        }
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}