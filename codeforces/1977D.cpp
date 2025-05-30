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
    int n,m;
    cin >> n >> m;
    vector<uint64_t> hsh(n);
    for(auto &x:hsh){
        x=rng64();
    }
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    map<uint64_t,int> dp;
    for(int i=0;i<m;i++){
        uint64_t sum=0;
        for(int j=0;j<n;j++){
            if(a[j][i]=='1'){
                sum^=hsh[j];
            }
        }
        for(int j=0;j<n;j++){
            dp[sum^hsh[j]]++;
        }
    }
    pair<int,uint64_t> ans(-1,0LL);
    for(auto [x,y]:dp){
        ans=max(ans,make_pair(y,x));
    }
    cout << ans.first << "\n";
    for(int i=0;i<m;i++){
        uint64_t sum=0;
        vector<int> res(n,0);
        for(int j=0;j<n;j++){
            if(a[j][i]=='1'){
                sum^=hsh[j];
                res[j]^=1;
            }
        }
        for(int j=0;j<n;j++){
            if((sum^hsh[j])==ans.second){
                res[j]^=1;
                for(auto x:res){
                    cout << x;
                }
                cout << "\n";
                return;
            }
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}