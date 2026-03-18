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
    int n,m,q;
    cin >> n >> m >> q;
    vector<int> a(n),b(m);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    sort(a.rbegin(),a.rend());
    sort(b.rbegin(),b.rend());
    vector<ll> fa(n+1),fb(m+1);
    for(int i=0;i<n;i++)fa[i+1]=fa[i]+a[i];
    for(int i=0;i<m;i++)fb[i+1]=fb[i]+b[i];
    while(q--){
        int x,y,z;
        cin >> x >> y >> z;
        int l=1,r=1e9;
        auto check=[&](int mid){
            int ai=min(int(upper_bound(a.begin(),a.end(),mid,greater<int>())-a.begin()),x);
            int bi=min(int(upper_bound(b.begin(),b.end(),mid,greater<int>())-b.begin()),y);
            return make_pair(ai+bi,fa[ai]+fb[bi]);
        };
        while(l<r){
            int mid=(l+r+1)/2;
            if(check(mid).first>=z)l=mid;
            else r=mid-1;
        }
        auto [cnt,val]=check(l);
        assert(cnt>=z);
        cout << val-1LL*(cnt-z)*l << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}