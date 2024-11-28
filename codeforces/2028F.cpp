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

const int M=10001;

using DS = bitset<M>;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<ll,DS>> dp;
    dp.emplace_back(1,DS());
    dp[0].second[0]=1;
    int consec=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        vector<pair<ll,DS>> ndp;
        DS cur;
        for(auto &[add,bs]:dp){
            add=min(add*x,(ll)m+1);
            if(!ndp.empty()&&ndp.back().first==add){
                ndp.back().second|=bs;
            }else{
                ndp.emplace_back(add,bs);
            }
            cur|=bs<<add;
        }
        ndp.emplace_back(1,cur);
        dp=move(ndp);
    }
    cout << (dp.back().second[m]?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}