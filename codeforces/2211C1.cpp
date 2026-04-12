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
    int n,k;
    cin >> n >> k;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    vector<bool> f(k);
    for(int i=0;i<n;i++){
        if(b[i]!=-1&&a[i]!=b[i]){
            f[i%k]=true;
        }
    }
    for(int i=0;i+k<n;i++){
        if(f[i%k]){
            if(a[i]!=a[i+k]||(b[i]!=-1&&b[i+k]!=-1&&b[i]!=b[i+k])){
                cout << "NO\n";
                return;
            }
        }
    }
    multiset<int> ms;
    for(int i=0;i<k;i++){
        if((f[i]||i+k>=n)){
            ms.emplace(a[i]);
        }
    }
    for(int i=0;i<k;i++){
        if((f[i]||i+k>=n)&&b[i]!=-1){
            auto it=ms.find(b[i]);
            if(it==ms.end()){
                cout << "NO\n";
                return;
            }
            ms.erase(it);
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}