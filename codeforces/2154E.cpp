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
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    sort(a.begin(),a.end());
    auto f=a;
    for(int i=1;i<n;i++){
        f[i]+=f[i-1];
    }
    ll ans=0;
    vector<pair<ll,ll>> block,pref;
    block.emplace_back(0,0);
    pref.emplace_back(0,0);
    for(int i=0;i<n;i++){
        int l=0,r=min(n-i-1,(int)block.size()-1);
        while(l<r){
            int m=(l+r+1)/2;
            if(a[i+m]-a[i]<=a[i]*block[m].second-block[m].first){
                l=m;
            }else{
                r=m-1;
            }
        }
        ans=max(ans,a[i]*l-f[i+l]+f[i]+a[i]*pref[l].second-pref[l].first);
        if(i%k==0){
            block.emplace_back(0,0);
            pref.emplace_back(pref.back());
        }
        block.back().first+=a[i];
        block.back().second++;
        pref.back().first+=a[i];
        pref.back().second++;
    }
    cout << ans+f[n-1] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}