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
    int n,m;
    cin >> n >> m;
    if(n>m){
        cout << 1 << " " << 1 << "\n";
        return;
    }
    vector<ll> f(n);
    for(int i=0;i<n;i++){
        int v=(m-i+1)/2;
        int c=0;
        for(int j=19;j>=0;j--){
            if(!(i>>j&1))c++;
        }
        for(int j=19;j>=0;j--){
            if(!(i>>j&1))c--;
            if(v>>j&1)f[i]+=1<<c;
        }
        f[i]<<=__builtin_popcount(i);
    }
    int opt=min_element(f.begin(),f.end())-f.begin();
    cout << opt+1 << " " << n << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}