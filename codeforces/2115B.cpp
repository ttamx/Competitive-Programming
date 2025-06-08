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
    int n,q;
    cin >> n >> q;
    vector<int> b(n);
    for(auto &x:b)cin >> x;
    vector<tuple<int,int,int>> qr(q);
    for(auto &[x,y,z]:qr){
        cin >> x >> y >> z;
        x--,y--,z--;
    }
    auto a=b;
    reverse(qr.begin(),qr.end());
    for(auto [x,y,z]:qr){
        int cur=a[z];
        a[z]=1;
        a[x]=max(a[x],cur);
        a[y]=max(a[y],cur);
    }
    reverse(qr.begin(),qr.end());
    auto c=a;
    for(auto [x,y,z]:qr){
        c[z]=min(c[x],c[y]);
    }
    if(b!=c){
        cout << "-1\n";
    }else{
        for(auto x:a){
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}