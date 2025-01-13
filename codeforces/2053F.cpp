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
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n,vector<int>(m));
    vector<ll> rem(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
            if(a[i][j]==-1){
                rem[i]++;
            }else{
                a[i][j]--;
            }
        }
    }
    using T = tuple<ll,int,int>;
    priority_queue<T> pq;
    ll ans=0;
    vector<int> cnt2(k);
    for(int i=0;i+1<n;i++){
        for(auto x:a[i])if(x!=-1)cnt2[x]++;
        for(auto x:a[i+1])if(x!=-1)ans+=cnt2[x];
        for(auto x:a[i])if(x!=-1)cnt2[x]--;
    }
    vector<map<int,int>> cnt(n);
    for(int i=0;i<n;i++){
        if(!rem[i])continue;
        if(i>0){
            for(auto x:a[i-1]){
                if(x!=-1){
                    cnt[i][x]++;
                }
            }
        }
        if(i+1<n){
            for(auto x:a[i+1]){
                if(x!=-1){
                    cnt[i][x]++;
                }
            }
        }
    }
    ll mx=0,lz=0,mx2=-LINF,lzmx=-LINF;
    vector<ll> dp(k);
    vector<int> last(k);
    vector<ll> f(n);
    for(int i=1;i<n;i++){
        f[i]=f[i-1]+rem[i-1]*rem[i];
    }
    for(int i=0;i<n;i++){
        vector<pair<int,ll>> upd;
        for(auto [x,c]:cnt[i]){
            upd.emplace_back(x,mx+lz+c*rem[i]);
            upd.emplace_back(x,max(dp[x],lzmx)+lz+c*rem[i]+(i>0?rem[i]*rem[i-1]:0LL));
        }
        if(i>0){
            lz+=rem[i]*rem[i-1];
        }
        for(auto [x,v]:upd){
            dp[x]=max(dp[x],v-lz);
            mx=max(mx,dp[x]);
        }
        lzmx=max(lzmx,mx2-lz);
        mx2=mx+lz;
    }
    ll best=0;
    for(auto x:dp){
        best=max(best,max(x,lzmx)+lz);
    }
    cout << ans+best << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}