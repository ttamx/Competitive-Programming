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
    vector<int> mx(n+1,-INF),mn(n+1,INF);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        mn[x]=min(mn[x],i);
        mx[x]=max(mx[x],i);
    }
    int l=0,r=n-1;
    for(int s=1;s<=n;s++){
        mn[s]=min(mn[s],mn[s-1]);
        mx[s]=max(mx[s],mx[s-1]);
        if(mx[s]-mn[s]+1>s){
            cout << 0 << "\n";
            return;
        }
        l=max(l,mx[s]-s+1);
        r=min(r,mn[s]+s-1);
    }
    cout << max(r-l+1,0) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}