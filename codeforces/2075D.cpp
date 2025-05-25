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

const int N=62;

ll dp[N][N],new_dp[N][N],dp2[N][N];

void runcase(){
    ll x,y;
    cin >> x >> y;
    int a=0,b=0;
    while(x!=y){
        if(x>y){
            x>>=1;
            a++;
        }else{
            y>>=1;
            b++;
        }
    }
    ll ans=LINF;
    while(x!=0){
        ans=min(ans,dp[a][b]);
        x>>=1,y>>=1;
        a++,b++;
    }
    ans=min(ans,dp2[a][b]);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            dp[i][j]=new_dp[i][j]=LINF;
        }
    }
    dp[0][0]=new_dp[0][0]=0;
    for(int v=1;v<N;v++){
        ll c=1LL<<v;
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                if(i>=v){
                    new_dp[i][j]=min(new_dp[i][j],dp[i-v][j]+c);
                }
                if(j>=v){
                    new_dp[i][j]=min(new_dp[i][j],dp[i][j-v]+c);
                }
            }
        }
        for(int i=0;i<N;i++){
            for(int j=0;j<N;j++){
                dp[i][j]=new_dp[i][j];
            }
        }
    }
    for(int i=N-1;i>=0;i--){
        for(int j=N-1;j>=0;j--){
            dp2[i][j]=dp[i][j];
            if(i+1<N){
                dp2[i][j]=min(dp2[i][j],dp2[i+1][j]);
            }
            if(j+1<N){
                dp2[i][j]=min(dp2[i][j],dp2[i][j+1]);
            }
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}