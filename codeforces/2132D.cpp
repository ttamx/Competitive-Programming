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
    ll n;
    cin >> n;
    auto calc=[&](ll v){
        ll res=0;
        ll d=9;
        while(v>0){
            res+=v;
            v-=d;
            d*=10;
        }
        return res;
    };
    ll l=0,r=n;
    while(l<r){
        ll mid=(l+r+1)/2;
        if(calc(mid)<=n)l=mid;
        else r=mid-1;
    }
    string s=to_string(l+1).substr(0,n-calc(l));
    ll ans=0;
    for(auto x:s){
        ans+=x-'0';
    }
    ll add=0;
    ll cur=0;
    ll cnt=0;
    for(auto x:to_string(l+1)){
        add*=10;
        add+=cnt*45;
        for(int i=0;i<x-'0';i++){
            add+=cur+i;
        }
        cnt=cnt*10+x-'0';
        cur+=x-'0';
    }
    cout << ans+add << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}