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
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(int i=0;i<n;i++){
        b[a[i]]=i;
    }
    int k=1;
    while(k*k<n){
        k++;
    }
    vector<int> dp(n);
    auto upd=[&](int i){
        int u=i;
        for(int j=0;j<k;j++){
            u=a[u];
        }
        dp[i]=u;
    };
    for(int i=0;i<n;i++){
        upd(i);
    }
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int x,y;
            cin >> x >> y;
            x--,y--;
            swap(a[x],a[y]);
            swap(b[a[x]],b[a[y]]);
            upd(x),upd(y);
            for(int i=0,u=x,z=dp[x];i<k;i++){
                int v=b[u];
                z=b[z];
                dp[v]=z;
                u=v;
            }
            for(int i=0,u=y,z=dp[y];i<k;i++){
                int v=b[u];
                z=b[z];
                dp[v]=z;
                u=v;
            }
        }else{
            int u,x;
            cin >> u >> x;
            u--;
            for(;x>=k;x-=k){
                u=dp[u];
            }
            for(;x>0;x--){
                u=a[u];
            }
            cout << u+1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}