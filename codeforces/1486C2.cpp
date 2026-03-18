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
    auto ask=[&](int l,int r){
        if(l==r)return -1;
        cout << "? " << l << " " << r << endl;
        int res;
        cin >> res;
        return res;
    };
    auto answer=[&](int x){
        cout << "! " << x << endl;
    };
    int p=ask(1,n);
    if(ask(1,p)!=p){
        int l=p+1,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(ask(1,m)==p)r=m; 
            else l=m+1;
        }
        answer(l);
    }else{
        int l=1,r=p-1;
        while(l<r){
            int m=(l+r+1)/2;
            if(ask(m,n)==p)l=m;
            else r=m-1;
        }
        answer(l);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}