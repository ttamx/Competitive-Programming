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
    int n,q;
    cin >> n >> q;
    vector<vector<int>> dp(n,vector<int>(n,INF));
    int ans=0;
    vector<pair<int,int>> state;
    state.emplace_back(0,1);
    dp[0][1]=0;
    while(q--){
        char c;
        int x;
        cin >> c >> x;
        x--;
        vector<tuple<int,int,int>> upd;
        if(c=='L'){
            for(auto [l,r]:state){
                int d1=(x-l+n)%n;
                int d2=(r-l+n)%n;
                if(d1<d2){
                    upd.emplace_back(x,r,dp[l][r]+d1);
                }else{
                    upd.emplace_back(x,(x+1)%n,dp[l][r]+d1+(x+1-r+n)%n);
                }
            }
            for(auto [l,r]:state){
                int d1=(l-x+n)%n;
                int d2=(l-r+n)%n;
                if(d1<d2){
                    upd.emplace_back(x,r,dp[l][r]+d1);
                }else{
                    upd.emplace_back(x,(x+n-1)%n,dp[l][r]+d1+(r-x+1+n)%n);
                }
            }
        }else{
            for(auto [l,r]:state){
                int d1=(x-r+n)%n;
                int d2=(l-r+n)%n;
                if(d1<d2){
                    upd.emplace_back(l,x,dp[l][r]+d1);
                }else{
                    upd.emplace_back((x+1)%n,x,dp[l][r]+d1+(x+1-l+n)%n);
                }
            }
            for(auto [l,r]:state){
                int d1=(r-x+n)%n;
                int d2=(r-l+n)%n;
                if(d1<d2){
                    upd.emplace_back(l,x,dp[l][r]+d1);
                }else{
                    upd.emplace_back((x+n-1)%n,x,dp[l][r]+d1+(l-x+1+n)%n);
                }
            }
        }
        for(int i=0;i<n;i++){
            dp[i][x]=INF;
        }
        for(int i=0;i<n;i++){
            dp[x][i]=INF;
        }
        ans=INF;
        state.clear();
        for(auto [i,j,v]:upd){
            state.emplace_back(i,j);
            dp[i][j]=min(dp[i][j],v);
            ans=min(ans,v);
        }
        sort(state.begin(),state.end());
        state.erase(unique(state.begin(),state.end()),state.end());
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}