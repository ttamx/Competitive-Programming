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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<ll> b(n);
    for(int i=0;i<n;i++)b[i]=a[i]&-a[i];
    auto l=b,r=b;
    for(int i=0;i+1<n;i++){
        if(a[i]%a[i+1]==0){
            ll d=a[i]/a[i+1];
            if(d==(d&-d)){
                assert(d>1);
                ll v=b[i]/d*2;
                l[i]-=v-1;
            }
        }
        if(i>0)l[i]+=l[i-1];
    }
    for(int i=n-1;i>0;i--){
        if(a[i]%a[i-1]==0){
            ll d=a[i]/a[i-1];
            if(d==(d&-d)){
                assert(d>1);
                ll v=b[i]/d*2;
                r[i]-=v-1;
            }
        }
        if(i+1<n)r[i]+=r[i+1];
    }
    for(int i=0;i<n;i++){
        ll cur=b[i];
        if(i>0)cur+=l[i-1];
        if(i+1<n)cur+=r[i+1];
        if(cur>=k){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}