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
    ll x,y;
    cin >> x >> y;
    tuple<ll,ll,ll> ans(LINF,-1,-1);
    for(int cx=0;cx<2;cx++){
        for(int cy=0;cy<2;cy++){
            vector<vector<tuple<ll,ll,ll>>> dp(2,vector<tuple<ll,ll,ll>>(2,{LINF,-1LL,-1LL}));
            dp[0][0]={(cx?x:-x)+(cy?y:-y),0LL,0LL};
            int mx=(cx?-1:1),my=(cy?-1:1);
            for(int i=30;i>=0;i--){
                vector<vector<tuple<ll,ll,ll>>> ndp(2,vector<tuple<ll,ll,ll>>(2,{LINF,-1LL,-1LL}));
                int vx=(x>>i&1),vy=(y>>i&1);
                for(int sx=0;sx<2;sx++){
                    for(int sy=0;sy<2;sy++){
                        for(ll bx=0;bx<2;bx++){
                            for(ll by=0;by<2;by++){
                                if(bx&&by)continue;
                                int nx=sx,ny=sy;
                                if(sx==0&&bx!=vx){
                                    if((bx<vx)!=cx)continue;
                                    nx=1;
                                }
                                if(sy==0&&by!=vy){
                                    if((by<vy)!=cy)continue;
                                    ny=1;
                                }
                                auto [val,valx,valy]=dp[sx][sy];
                                ndp[nx][ny]=min(ndp[nx][ny],{val+mx*(bx<<i)+my*(by<<i),valx+(bx<<i),valy+(by<<i)});
                            }
                        }
                    }
                }
                dp=move(ndp);
            }
            for(int i=0;i<2;i++){
                for(int j=0;j<2;j++){
                    ans=min(ans,dp[i][j]);
                }
            }
        }
    }
    auto [_,xx,yy]=ans;
    cout << xx << " " << yy << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}