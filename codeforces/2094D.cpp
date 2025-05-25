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
    string s,t;
    cin >> s >> t;
    vector<pair<char,int>> a,b;
    for(auto x:s){
        if(!a.empty()&&a.back().first==x)a.back().second++;
        else a.emplace_back(x,1);
    }
    for(auto x:t){
        if(!b.empty()&&b.back().first==x)b.back().second++;
        else b.emplace_back(x,1);
    }
    if(a.size()!=b.size())return void(cout << "NO\n");
    for(int i=0;i<a.size();i++){
        if(a[i].first!=b[i].first)return void(cout << "NO\n");
        if(b[i].second<a[i].second||a[i].second*2<b[i].second)return void(cout << "NO\n");
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}