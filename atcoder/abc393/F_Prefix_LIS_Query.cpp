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

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i){
            t[i]=max(t[i],v);
        }
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i){
            res=max(res,t[i]);
        }
        return res;
    }
}f;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> v(q);
    vector<vector<int>> qr(n);
    for(int i=0;i<q;i++){
        int r;
        cin >> r >> v[i];
        r--;
        qr[r].emplace_back(i);
    }
    vector<int> lis;
    for(int i=0;i<n;i++){
        
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}