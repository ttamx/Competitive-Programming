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
    ll k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    auto find_high=[&](ll c){
        ll l=0,r=1e6;
        while(l<r){
            ll mid=(l+r+1)/2;
            ll cnt=0;
            for(auto x:a){
                cnt+=max(0LL,x-mid+1);
            }
            if(cnt>=c)l=mid;
            else r=mid-1;
        }
        return l;
    };
    auto find_low=[&](ll c){
        ll l=0,r=1e6;
        while(l<r){
            ll mid=(l+r)/2;
            ll cnt=0;
            for(auto x:a){
                cnt+=max(0LL,mid-x);
            }
            if(cnt>=c)r=mid;
            else l=mid+1;
        }
        return l;
    };
    ll l=0,r=accumulate(a.begin(),a.end(),0LL);
    while(l<r){
        ll mid=(l+r+1)/2;
        ll high=find_high(mid);
        ll low=find_low(mid);
        if(high-low>k)l=mid;
        else r=mid-1;
    }
    ll high=find_high(l);
    ll low=find_low(l);
    assert(low<high);
    ll clow=l,chigh=l;
    ll ans=l*k;
    // cerr << "LOW: " << low << " HIGH: " << high << "\n";
    for(auto &x:a){
        if(x<low-1){
            ll used=min(clow,low-x-1);
            clow-=used;
            x+=used;
        }
        if(x>high){
            ll used=min(chigh,x-high);
            chigh-=used;
            x-=used;
        }
        // cerr << x << " ";
    }
    // cerr << "\n";
    // cerr << clow << " " << chigh << "\n";
    for(auto &x:a){
        if(x<low){
            assert(x==low-1);
            if(clow>0){
                clow--;
                x++;
            }
        }
        if(x>=high){
            assert(x==high);
            if(chigh>0){
                chigh--;
                x--;
            }
        }
        ans+=x*(x+1)/2;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}