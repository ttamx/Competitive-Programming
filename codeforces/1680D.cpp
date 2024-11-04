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
    ll ans=-1;
    for(int t=0;t<4;t++){
        if(t==2){
            for(auto &x:a){
                x=-x;
            }
        }
        vector<ll> mx(n+1),mn(n+1);
        for(int i=n-1;i>=0;i--){
            mx[i]=mx[i+1]-(a[i]==0?-k:a[i]);
            mn[i]=mn[i+1]-(a[i]==0?k:a[i]);
        }
        if(mx[0]<0||mn[0]>0){
            continue;
        }
        for(int i=0;i<=n;i++){
            ll l=0,r=0,p=0;
            for(int j=0;j<n;j++){
                if(a[j]){
                    p+=a[j];
                }else if(j<i){
                    p=max(p-k,mn[j+1]);
                }else{
                    p=min(p+k,mx[j+1]);
                }
                l=min(l,p);
                r=max(r,p);
            }
            ans=max(ans,r-l+1);
        }
        reverse(a.begin(),a.end());
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}