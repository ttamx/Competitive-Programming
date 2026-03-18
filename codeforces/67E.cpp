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

ll floor(ll a,ll b){
    return a/b-((a^b)<0&&a%b);
}

ll ceil(ll a,ll b){
    return floor(a+b-1,b);
}

void runcase(){
    int n;
    cin >> n;
    vector<pair<ll,ll>> a(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
    }
    assert(a[0].second==a[1].second);
    ll base=a[0].second;
    if(a[0].first>a[1].first){
        for(auto &[x,y]:a){
            x=-x,y=-y;
        }
    }
    ll l=a[0].first,r=a[1].first;
    for(int i=2;i<n;i++){
        auto [xi,yi]=a[i];
        for(int j=i+1;j<n;j++){
            auto [xj,yj]=a[j];
            if(yi==yj){
                if(xi<xj){
                    cout << 0 << "\n";
                    return;
                }
                continue;
            }
            if(yi<yj){
                l=max(l,xi+ceil((base-yi)*(xj-xi),yj-yi));
            }else{
                r=min(r,xi+floor((base-yi)*(xj-xi),yj-yi));
            }
        }
    }
    cout << max(0LL,r-l+1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}