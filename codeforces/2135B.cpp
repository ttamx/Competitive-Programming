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

const bool LOCAL=false;

void runcase(){
    ll xx,yy;
    if(LOCAL){
        cin >> xx >> yy;
    }
    int n;
    cin >> n;
    vector<pair<ll,ll>> a(n);
    ll mn1=LINF,mn2=LINF;
    for(auto &[x,y]:a){
        cin >> x >> y;
        mn1=min(mn1,x+y);
        mn2=min(mn2,y-x);
    }
    auto ask=[&](char dir,ll k){
        cout << "? " << dir << " " << k << endl;
        ll res=LINF;
        if(LOCAL){
            if(dir=='U')yy+=k;
            if(dir=='D')yy-=k;
            if(dir=='L')xx-=k;
            if(dir=='R')xx+=k;
            for(auto [x,y]:a){
                res=min(res,abs(x-xx)+abs(y-yy));
            }
            return res;
        }
        cin >> res;
        return res;
    };
    ll k=1'000'000'000;
    ask('D',k);
    ask('D',k);
    ask('L',k);
    ll v1=mn1-ask('L',k)+4*k;
    ask('R',k);
    ask('R',k);
    ask('R',k);
    ll v2=mn2-ask('R',k)+4*k;
    cout << "! " << (v1-v2)/2 << " " << (v1+v2)/2 << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}