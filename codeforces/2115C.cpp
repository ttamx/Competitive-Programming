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
    int n,m,pp;
    cin >> n >> m >> pp;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int mn=*min_element(a.begin(),a.end());
    int tot=accumulate(a.begin(),a.end(),0)-n;
    db p=db(pp)/100.0;
    db q=1.0-p;
    vector<vector<db>> dp(m+1,vector<db>(mn)),upd1(m+1,vector<db>(mn)),upd2(m+1,vector<db>(mn));
    set<pair<int,int>> qu;
    for(int i=0;i<=m;i++){
        for(int j=0;j<mn&&i+j<=m;j++){
            if(i+j*n==tot){
                dp[i][j]=1.0;
                qu.emplace(i,j);
            }
        }
    }
    for(int t=0;t<m;t++){
        set<pair<int,int>> nqu;
        for(auto [i,j]:qu){
            if(i>0&&dp[i][j]-dp[i-1][j]>EPS){
                nqu.emplace(i-1,j);
            }
            if(j>0&&dp[i][j]-dp[i][j-1]>EPS){
                nqu.emplace(i,j-1);
            }
        }
        for(auto [i,j]:nqu){
            db tmp=dp[i][j];
            if(i+1<=m)dp[i][j]+=max(dp[i+1][j]-tmp,0.l)*q;
            if(j+1<mn)dp[i][j]+=max(dp[i][j+1]-tmp,0.l)*p;
            qu.emplace(i,j);
        }
    }
    cout << dp[0][0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    cout << fixed << setprecision(9);
    while(t--)runcase();
}