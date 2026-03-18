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
    vector<int> a(n),c(n);
    ll tot=0;
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:c){
        cin >> x;
        tot+=x;
    }
    map<int,ll> dat;
    auto insert=[&](int i,ll v){
        i=-i;
        auto it=dat.lower_bound(i);
        if(it!=dat.end()&&it->second>=v)return;
        it=dat.insert(it,{i,v});
        it->second=v;
        while(it!=dat.begin()&&prev(it)->second<=v){
            dat.erase(prev(it));
        }
    };
    auto query=[&](int i){
        i=-i;
        return dat.lower_bound(i)->second;
    };
    insert(0,0);
    ll ans=0;
    for(int i=0;i<n;i++){
        ll cur=query(a[i])+c[i];
        insert(a[i],cur);
        ans=max(ans,cur);
    }
    cout << tot-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}