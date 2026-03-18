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

const int N=2e5+5;

int n,q,k;
int a[N],b[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> q;
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        a[l]++,a[r+1]--;
    }
    for(int i=1;i<N;i++){
        a[i]+=a[i-1];
        b[i]=b[i-1]+(a[i]>=k);
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        cout << b[r]-b[l-1] << "\n";
    }
}