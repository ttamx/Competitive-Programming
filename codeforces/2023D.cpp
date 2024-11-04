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

const int P=105;
const int W=2e5+5;

int n;
ll base=0;
db dp[W];
db ans=0;
vector<int> vals[P];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        int p,w;
        cin >> p >> w;
        if(p==100){
            base+=w;
        }else{
            vals[p].emplace_back(w);
        }
    }
    vector<pair<int,int>> a;
    for(int i=1;i<100;i++){
        sort(vals[i].rbegin(),vals[i].rend());
        for(int j=0;j<vals[i].size()&&j*(100-i)<i;j++){
            a.emplace_back(i,vals[i][j]);
        }
    }
    dp[0]=1;
    for(auto [p,w]:a){
        db q=db(p)/100;
        for(int i=W-1-w;i>=0;i--){
            dp[i+w]=max(dp[i+w],dp[i]*q);
        }
    }
    cout << fixed << setprecision(15);
    for(int i=0;i<W;i++){
        ans=max(ans,(base+i)*dp[i]);
    }
    cout << ans;
}