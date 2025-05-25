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

const int N=3e5+5;

int n;
int a[N];
int mu[N];
vector<int> divisors[N];
ll dp[N],dp2[N];
ll ans=0;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    mu[1]=1;
    for(int i=1;i<N;i++){
        for(int j=i*2;j<N;j+=i){
            mu[j]-=mu[i];
        }
    }
    for(int i=1;i<N;i++){
        for(int j=i;j<N;j+=i){
            divisors[j].emplace_back(i);
        }
    }
    cin >> n;
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    sort(a,a+n);
    for(int i=0;i<n;i++){
        for(auto d:divisors[a[i]]){
            ans+=dp[d]*(i-1)*mu[d];
            ans-=dp2[d]*mu[d];
        }
        for(auto d:divisors[a[i]]){
            dp[d]++;
            dp2[d]+=i;
        }
    }
    cout << ans << "\n";
}