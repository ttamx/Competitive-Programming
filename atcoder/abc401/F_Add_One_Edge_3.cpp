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
    ll base=0;
    auto work=[&](){
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        for(int i=0;i<n-1;i++){
            int u,v;
            cin >> u >> v;
            u--,v--;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        vector<int> dp(n),up(n);
        function<void(int,int)> dfs=[&](int u,int p){
            for(auto v:adj[u])if(v!=p){
                dfs(v,u);
                dp[u]=max(dp[u],dp[v]+1);
            }
        };
        function<void(int,int)> dfs2=[&](int u,int p){
            for(int t=0;t<2;t++){
                int cur=0;
                for(auto v:adj[u])if(v!=p){
                    up[v]=max(up[v],cur);
                    cur=max(cur,dp[v]+1);
                }
                reverse(adj[u].begin(),adj[u].end());
            }
            for(auto v:adj[u])if(v!=p){
                up[v]=max(up[v],up[u]+1);
                dfs2(v,u);
            }
        };
        up[0]=-1;
        dfs(0,-1);
        dfs2(0,-1);
        for(int i=0;i<n;i++)dp[i]=max(dp[i],up[i]+1);
        sort(dp.begin(),dp.end());
        base=max(base,(ll)dp.back());
        return make_pair(n,dp);
    };
    auto [n,a]=work();
    auto [m,b]=work();
    ll ans=0,sum=0,cnt=0;
    for(auto x:b){
        while(!a.empty()&&a.back()+x+1>base){
            sum+=a.back();
            cnt++;
            a.pop_back();
        }
        ans+=(x+1)*cnt+sum+base*a.size();
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}