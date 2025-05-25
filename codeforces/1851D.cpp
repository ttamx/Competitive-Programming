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
    vector<ll> a(n-1);
    for(auto &x:a)cin >> x;
    ll s=1LL*n*(n+1)/2;
    if(a.back()!=s){
        if(a.back()>s){
            cout << "NO\n";
            return;
        }
        a.emplace_back(s);
        vector<bool> f(n);
        ll p=0;
        for(auto x:a){
            ll v=x-p;
            if(v>n||f[v-1]){
                cout << "NO\n";
                return;
            }
            if(v<=n)f[v-1]=true;
            p=x;
        }
        cout << "YES\n";
        return;
    }
    vector<bool> f(n);
    ll p=0;
    for(auto x:a){
        ll v=x-p;
        if(v<=n)f[v-1]=true;
        p=x;
    }
    cout << ((count(f.begin(),f.end(),true)>=n-2)?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}