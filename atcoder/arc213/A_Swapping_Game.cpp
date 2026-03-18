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
    vector<vector<int>> p(n+1,vector<int>(m));
    vector<vector<int>> q(n+1,vector<int>(m));
    vector<int> c(n+1);
    iota(p[0].begin(),p[0].end(),0);
    for(int i=1;i<=n;i++){
        cin >> c[i];
        for(int j=0;j<m;j++){
            cin >> p[i][j];
            p[i][j]--;
            q[i][p[i][j]]=j;
        }
    }
    auto calc=[&](int x,int y){
        int res=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<i;j++){
                if(q[x][p[y][j]]>q[x][p[y][i]]){
                    res++;
                }
            }
        }
        return res;
    };
    vector<ll> dp(n+1);
    ll mx=-LINF;
    for(int i=1;i<=n;i++){
        dp[i]=mx+c[i];
        for(int j=max(0,i-50);j<i;j++){
            if(calc(i,j)<=i-j){
                dp[i]=max(dp[i],dp[j]+c[i]);
            }
        }
        if(i>=50){
            mx=max(mx,dp[i-50]);
        }
    }
    cout << *max_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}