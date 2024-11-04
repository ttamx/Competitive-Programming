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
    int n,k,q;
    cin >> k >> q;
    n=1<<k;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> t(2*n),op(2*n);
    function<void(int,int,int,int)> build=[&](int l,int r,int i,int d){
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2,d^1);
        build(m+1,r,i*2+1,d^1);
        if(d)t[i]=t[i*2]|t[i*2+1];
        else t[i]=t[i*2]^t[i*2+1];
    };
    function<void(int,int,int,int,int,int)> update=[&](int l,int r,int i,int d,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,d^1,x,v);
        update(m+1,r,i*2+1,d^1,x,v);
        if(d)t[i]=t[i*2]|t[i*2+1];
        else t[i]=t[i*2]^t[i*2+1];
    };
    build(0,n-1,1,k&1);
    while(q--){
        int x,v;
        cin >> x >> v;
        x--;
        update(0,n-1,1,k&1,x,v);
        cout << t[1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}