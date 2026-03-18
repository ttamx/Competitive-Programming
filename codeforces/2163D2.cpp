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
    auto ask=[&](int l,int r){
        cout << "? " << l << " " << r << endl;
        int res;
        cin >> res;
        return res;
    };
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(m),b;
    for(auto &[r,l]:a){
        cin >> l >> r;
    }
    sort(a.begin(),a.end());
    for(auto [r,l]:a){
        if(!b.empty()&&b.back().second==r){
            continue;
        }
        while(!b.empty()&&b.back().first>=l){
            b.pop_back();
        }
        b.emplace_back(l,r);
    }
    m=b.size();
    int ans=0;
    int l=0,r=m-1;
    while(l<=r){
        int mid=(l+r)/2;
        int vl=ask(1,b[mid].second);
        int vr=ask(b[mid].first,n);
        ans=max(ans,min(vl,vr));
        if(vl<vr)l=mid+1;
        else r=mid-1;
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}