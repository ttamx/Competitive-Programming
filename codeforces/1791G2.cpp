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
    ll c;
    cin >> n >> c;
    vector<pair<ll,ll>> a;
    for(int i=1;i<=n;i++){
        ll x;
        cin >> x;
        a.emplace_back(x+min(i,n-i+1),x+i);
    }
    sort(a.begin(),a.end());
    int p=0;
    vector<ll> b(n);
    for(int i=0;i<n;i++){
        b[i]=a[i].first;
    }
    for(int i=1;i<n;i++){
        b[i]+=b[i-1];
    }
    int ans=0;
    for(int i=0;i<n;i++){
        if(c<a[i].second){
            continue;
        }
        int j=upper_bound(b.begin(),b.end(),c-a[i].second)-b.begin();
        if(j>i){
            j=upper_bound(b.begin(),b.end(),c-a[i].second+a[i].first)-b.begin();
            ans=max(ans,j);
        }else{
            ans=max(ans,j+1);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}