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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> mn(n);
    mn[n-1]=n-1;
    for(int i=n-2;i>=0;i--){
        mn[i]=a[i]>a[mn[i+1]]?mn[i+1]:i;
    }
    vector<int> b,c;
    int pos=0;
    for(int i=0;i<n;i++){
        i=mn[i];
        b.emplace_back(a[i]);
        for(;pos<i;pos++){
            c.emplace_back(a[pos]+1);
        }
        pos=i+1;
    }
    for(;pos<n;pos++){
        c.emplace_back(a[pos]+1);
    }
    sort(c.begin(),c.end());
    if(!c.empty()){
        while(!b.empty()&&b.back()>c[0]){
            c.emplace_back(b.back()+1);
            b.pop_back();
        }
        sort(c.begin(),c.end());
    }
    b.insert(b.end(),c.begin(),c.end());
    for(auto x:b){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}