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
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    ll mx=*max_element(a.begin(),a.end());
    vector<ll> m(n*2+5),c(n*2+5);
    ll h=n/2;
    for(int i=0;i<n;i++){
        ll v=mx-a[i];
        m[i+2]-=v;
        m[i+h*2+2]+=v;
        c[i]+=h*v;
        m[i+3]+=v;
        m[i+(h-1)*2+3]-=v;
        c[i+(h-1)*2+3]-=(h-1)*v;
    }
    for(int i=0;i<2*n;i++){
        if(i>=2){
            m[i]+=m[i-2];
            c[i]+=c[i-2]+m[i];
        }
    }
    for(int i=0;i<n;i++){
        cout << c[i]+c[i+n] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}