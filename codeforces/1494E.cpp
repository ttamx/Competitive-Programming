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
    int n,q;
    cin >> n >> q;
    int cnt1=0,cnt2=0;
    set<pair<int,int>> s1;
    set<tuple<int,int,char>> s2;
    map<pair<int,int>,char> mp;
    while(q--){
        char op;
        cin >> op;
        if(op=='+'){
            int u,v;
            char c;
            cin >> u >> v >> c;
            if(s1.count({v,u})){
                cnt1++;
            }
            if(s2.count({v,u,c})){
                cnt2++;
            }
            s1.emplace(u,v);
            s2.emplace(u,v,c);
            mp[{u,v}]=c;
        }else if(op=='-'){
            int u,v;
            cin >> u >> v;
            char c=mp[{u,v}];
            if(s1.count({v,u})){
                cnt1--;
            }
            if(s2.count({v,u,c})){
                cnt2--;
            }
            s1.erase({u,v});
            s2.erase({u,v,c});
        }else{
            int k;
            cin >> k;
            if(k&1){
                cout << (cnt1?"YES":"NO") << "\n";
            }else{
                cout << (cnt2?"YES":"NO") << "\n";
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}