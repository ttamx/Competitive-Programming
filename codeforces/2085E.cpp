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

const int N=1e6+5;

int cnt[N];

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    ll mn=b[n-1];
    if(a==b)return void(cout << mn+1 << "\n");  
    vector<int> c;
    ll v=accumulate(a.begin(),a.end(),0LL)-accumulate(b.begin(),b.end(),0LL);
    if(v<0)return void(cout << "-1\n");
    for(ll i=1;i*i<=v;i++){
        if(v%i)continue;
        if(i>mn)c.emplace_back(i);
        if(i*i<v&&v/i>mn)c.emplace_back(v/i);
    }
    auto check=[&](int k){
        for(auto x:a)cnt[x%k]++;
        for(auto x:b)if(--cnt[x%k]<0){
            cnt[x%k]=0;
            for(auto y:a)cnt[y%k]=0;
            return false;
        }
        for(auto x:a)cnt[x%k]=0;
        return true;
    };
    for(auto k:c)if(check(k))return void(cout << k << "\n");
    cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}