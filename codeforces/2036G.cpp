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

const bool AUTO=false;

auto myassert(bool x){
    if(!x){
        while(true);
    }
}

void runcase(){
    ll n;
    if(AUTO){
        n=1e18;
    }else{
        cin >> n;
    }
    int query_cnt=0;
    ll aa,bb,cc;
    if(AUTO){
        aa=rng()%n+1;
        bb=rng()%n+1;
        cc=aa^bb;
        if(cc>n){
            cc=rng()%n+1;
        }
    }
    auto ask=[&](ll l,ll r){
        query_cnt++;
        myassert(query_cnt<=150);
        myassert(1<=l&&l<=r&&r<=n);
        if(AUTO){
            ll res=0;
            if(l<=aa&&aa<=r)res^=aa;
            if(l<=bb&&bb<=r)res^=bb;
            if(l<=cc&&cc<=r)res^=cc;
            return res;
        }
        cout << "xor " << l << " " << r << endl;
        ll res;
        cin >> res;
        return res;
    };
    ll all=ask(1,n);
    auto answer=[&](ll a,ll b){
        if(AUTO){
            vector<ll> x{aa,bb,cc};
            vector<ll> y{a,b,(a^b^all)};
            sort(x.begin(),x.end());
            sort(y.begin(),y.end());
            cout << "ANSWER ";
            for(auto v:x)cout << v << " ";
            cout << "\n";
            cout << "OUTPUT ";
            for(auto v:y)cout << v << " ";
            cout << "\n";
            cout << flush;
            assert(x==y);
            cout << "PASSED\n";
            return;
        }
        cout << "ans " << a << " " << b << " " << (all^a^b) << endl;
    };
    if(all!=0){
        ll a,b;
        {
            ll l=1,r=n;
            while(l<r){
                ll m=(l+r)/2;
                if(ask(1,m)!=0){
                    r=m;
                }else{
                    l=m+1;
                }
            }
            a=l;
        }
        {
            ll l=a+1,r=n-1;
            while(l<r){
                ll m=(l+r)/2;
                if(ask(1,m)!=a){
                    r=m;
                }else{
                    l=m+1;
                }
            }
            b=l;
        }
        answer(a,b);
        return;
    }
    ll part=2;
    ll a;
    while((a=ask(1,part-1))==0){
        part*=2;
    }
    ll b;
    {
        ll l=part,r=n-1;
        while(l<r){
            ll m=(l+r)/2;
            if(ask(1,m)!=a){
                r=m;
            }else{
                l=m+1;
            }
        }
        b=l;
        b=l;
    }
    answer(a,b);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}