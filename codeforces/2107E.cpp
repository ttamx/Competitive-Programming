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
    ll kk;
    cin >> n >> kk;
    for(int t=-1;t<=1;t++){
        ll k=kk+t;
        vector<int> a;
        for(int i=n-1;i>=2;i--){
            ll v=1LL*i*(i-1)/2;
            if(k>=v){
                k-=v;
                a.emplace_back(i);
            }
        }
        if(k==0){
            cout << "Yes\n";
            int cur=1;
            int sz=n;
            a.emplace_back(1);
            for(auto x:a){
                int p=cur;
                for(int i=0;i<sz-x;i++){
                    cout << p << " " << ++cur << "\n";
                }
                sz=x;
            }
            return;
        }
    }
    cout << "No\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}