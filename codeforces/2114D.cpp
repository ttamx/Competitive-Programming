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
    vector<pair<int,int>> a(n);
    pair<int,int> hmn(INF,INF),hmx(0,0),wmn(INF,INF),wmx(0,0);
    for(auto &[x,y]:a){
        cin >> x >> y;
        hmn.second=min(hmn.second,x);
        if(hmn.second<hmn.first)swap(hmn.first,hmn.second);
        hmx.second=max(hmx.second,x);
        if(hmx.second>hmx.first)swap(hmx.first,hmx.second);
        wmn.second=min(wmn.second,y);
        if(wmn.second<wmn.first)swap(wmn.first,wmn.second);
        wmx.second=max(wmx.second,y);
        if(wmx.second>wmx.first)swap(wmx.first,wmx.second);
    }
    if(n==1){
        cout << 1 << "\n";
        return;
    }
    ll ans=LINF;
    for(auto [x,y]:a){
        ll hx=hmx.first==x?hmx.second:hmx.first;
        ll hn=hmn.first==x?hmn.second:hmn.first;
        ll wx=wmx.first==y?wmx.second:wmx.first;
        ll wn=wmn.first==y?wmn.second:wmn.first;
        ll area=(wx-wn+1)*(hx-hn+1);
        if(area==n-1){
            area=min((wx-wn+2)*(hx-hn+1),(wx-wn+1)*(hx-hn+2));
        }
        ans=min(ans,area);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}