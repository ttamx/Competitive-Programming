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

const int D=100;

ll calc(ll v,int k){
    vector<int> a;
    for(;v;v/=4)a.emplace_back(v%4);
    reverse(a.begin(),a.end());
    vector<vector<ll>> dp(k+1,vector<ll>(D));
    dp[0][0]=1;
    for(auto x:a){
        vector<vector<ll>> ndp(k+1,vector<ll>(D));
        for(int i=0;i<=k;i++){
            for(int d=0;d<D;d++){
                for(int t=0;t<=4&&i+t<=k;t++){
                    if(t==4&&i+t<k)continue;
                    int nd=min(d*4+x-t-i,D-1);
                    if(nd<0)continue;
                    ndp[i+t][nd]+=dp[i][d];
                }
            }
        }
        dp=move(ndp);
    }
    return accumulate(dp[k].begin(),dp[k].end(),0LL);
}

void runcase(){
    ll l,r,k;
    cin >> l >> r >> k;
    if(k>91){
        cout << 0 << "\n";
        return;
    }
    cout << calc(r,k)-calc(l-1,k) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}