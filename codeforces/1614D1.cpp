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

const int N=5e6+5;

int n;
ll cnt[N],dp[N];
int cur;
int prime[N],lp[N];
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    for(int i=2;i<N;i++){
        if(lp[i]==0){
            lp[i]=i;
            prime[cur++]=i;
        }
        for(int j=0;j<cur&&i*prime[j]<N;j++){
            int p=prime[j];
            lp[i*p]=p;
            if(p==lp[i]){
                break;
            }
        }
    }
    for(int j=0;j<cur;j++){
        int p=prime[j];
        for(int i=(N-1)/p;i>=0;i--){
            cnt[i]+=cnt[i*p];
        }
    }
    dp[1]=cnt[1];
    for(int i=1;i<N;i++){
        for(int j=0;j<cur&&i*prime[j]<N;j++){
            int p=prime[j];
            dp[i*p]=max(dp[i*p],dp[i]+cnt[i*p]*(p-1)*i);
        }
        ans=max(ans,dp[i]);
    }
    cout << ans;
}