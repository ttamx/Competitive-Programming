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
    map<int,multiset<int>> a,b;
    ll area=0;
    ll mxh=0,mxw=0;
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y;
        a[x].emplace(y);
        b[y].emplace(x);
        area+=x*y;
        mxh=max(mxh,x);
        mxw=max(mxw,y);
    }
    auto aa=a,bb=b;
    auto erase=[&](int x,int y){
        a[x].erase(a[x].find(y));
        b[y].erase(b[y].find(x));
        if(a[x].empty())a.erase(x);
        if(b[y].empty())b.erase(y);
    };
    auto check=[&](auto &&self,int h,int w)->bool {
        if(h==0||w==0)return true;
        if(a.count(h)){
            int ww=*a[h].begin();
            erase(h,ww);
            return self(self,h,w-ww);
        }
        if(b.count(w)){
            int hh=*b[w].begin();
            erase(hh,w);
            return self(self,h-hh,w);
        }
        return false;
    };
    set<pair<ll,ll>> ans;
    if(area%mxh==0&&check(check,mxh,area/mxh)){
        ans.emplace(mxh,area/mxh);
    }
    a=aa,b=bb;
    if(area%mxw==0&&check(check,area/mxw,mxw)){
        ans.emplace(area/mxw,mxw);
    }
    cout << ans.size() << "\n";
    for(auto [h,w]:ans){
        cout << h << " " << w << "\n";
    }

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}