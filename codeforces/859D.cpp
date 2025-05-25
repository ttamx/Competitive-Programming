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
    int m=1<<n;
    vector<vector<int>> a(m,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<double> p(m,1.0),dp(m);
    for(int r=0;r<n;r++){
        vector<double> np(m),ndp(m);
        for(int g=0;g<m;g+=2<<r){
            for(int i=g;i<g+(1<<r);i++){
                for(int j=g+(1<<r);j<g+(2<<r);j++){
                    np[i]+=p[j]*a[i][j]/100.0;
                    ndp[i]=max(ndp[i],dp[j]);
                }
                np[i]*=p[i];
                ndp[i]+=dp[i]+np[i]*(1<<r);
            }
            for(int i=g+(1<<r);i<g+(2<<r);i++){
                for(int j=g;j<g+(1<<r);j++){
                    np[i]+=p[j]*a[i][j]/100.0;
                    ndp[i]=max(ndp[i],dp[j]);
                }
                np[i]*=p[i];
                ndp[i]+=dp[i]+np[i]*(1<<r);
            }
        }
        swap(p,np);
        swap(dp,ndp);
    }
    cout << fixed << setprecision(12) << *max_element(dp.begin(),dp.end()) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}