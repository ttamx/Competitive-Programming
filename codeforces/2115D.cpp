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
    vector<ll> a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    string s;
    cin >> s;
    ll ans=0;
    for(int t=59;t>=0;t--){
        int last=-1;
        ll cur=0;
        for(int i=0;i<n;i++){
            if((a[i]^b[i])>>t&1){
                last=i;
            }else{
                cur^=a[i]>>t&1;
            }
        }
        if(last==-1){
            ans^=cur<<t;
            continue;
        }
        ll p=s[last]-'0';
        ans^=p<<t;
        ll d=a[last]^b[last];
        if((cur^(a[last]>>t&1))==p){
            b[last]^=d;
        }else{
            a[last]^=d;
        }
        for(int i=0;i<last;i++){
            if((a[i]^b[i])>>t&1){
                if(a[i]>>t&1){
                    a[i]^=d;
                }else{
                    b[i]^=d;
                }
            }
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