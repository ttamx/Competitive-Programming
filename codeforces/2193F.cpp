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
    int n,sx,sy,tx,ty;
    cin >> n >> sx >> sy >> tx >> ty;
    vector<pair<int,int>> a(n);
    for(auto &x:a)cin >> x.first;
    for(auto &x:a)cin >> x.second;
    map<int,pair<int,int>> mp;
    for(auto [x,y]:a){
        if(!mp.count(x))mp[x]={y,y};
        mp[x].first=min(mp[x].first,y);
        mp[x].second=max(mp[x].second,y);
    }
    int pl=sy,pr=sy;
    ll vl=0,vr=0;
    for(auto [_,e]:mp){
        auto [l,r]=e;
        tie(vl,vr)=make_pair(r-l+min(vl+abs(r-pl),vr+abs(r-pr)),r-l+min(vl+abs(l-pl),vr+abs(l-pr)));
        pl=l,pr=r;
    }
    cout << min(vl+abs(ty-pl),vr+abs(ty-pr))+tx-sx << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}