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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> b(n),c(n),d(n);
    for(int i=0;i<n;i++){
        int cnt=0;
        for(int x=a[i];x>1;x/=2){
            b[i]++;
            if(x&1){
                cnt++;
            }
        }
        if((a[i]&1)&&cnt==1){
            d[i]=1;
        }else if(cnt>0){
            c[i]=1;
        }
    }
    vector<int> f(n+1),g(n+1),h(n+1);
    for(int i=0;i<n;i++){
        f[i+1]=f[i]+b[i];
        g[i+1]=g[i]+c[i];
        h[i+1]=h[i]+d[i];
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--;
        cout << f[r]-f[l]+g[r]-g[l]+(h[r]-h[l])/2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}