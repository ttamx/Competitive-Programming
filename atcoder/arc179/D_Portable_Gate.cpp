#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

const int N=2e5+5;

int n;
vi adj[N];
int dp[N][2][2],up[N][2][2];
int dif1[N],dif2[N];
pair<int,int> mx1[N],mx2[N];
int ans=INF;

void dfs(int u,int p=0){
    for(auto v:adj[u])if(v!=p)dfs(v,u);
    for(auto v:adj[u])if(v!=p){
        dp[u][1][0]+=dp[v][1][0]+2;
        dif1[v]=dp[v][1][0]-dp[v][0][0]+1;
        mx1[u].second=max(mx1[u].second,dif1[v]);
        if(mx1[u].second>mx1[u].first)swap(mx1[u].first,mx1[u].second);
    }
    dp[u][0][0]=dp[u][1][0]-mx1[u].first;
    for(auto v:adj[u])if(v!=p){
        int val=min(dp[v][1][1]+2,dp[v][0][0]+1);
        dp[u][1][1]+=val;
        dif2[v]=val-min(dp[v][0][1],dp[v][0][0])-1;
        mx2[u].second=max(mx2[u].second,dif2[v]);
        if(mx2[u].second>mx2[u].first)swap(mx2[u].first,mx2[u].second);
    }
    dp[u][0][1]=dp[u][1][1]-mx2[u].first;
}

void dfs2(int u,int p=0){
    for(auto v:adj[u])if(v!=p){
        if(p){
            up[v][1][0]=dp[u][1][0]-dp[v][1][0]+up[u][1][0];
            int mx=up[u][1][0]-up[u][0][0]+1;
            mx=max(mx,dif1[v]==mx1[u].first?mx1[u].second:mx1[u].first);
            up[v][0][0]=up[v][1][0]-mx;
        }else{
            up[v][1][0]=dp[u][1][0]-dp[v][1][0]-2;
            up[v][0][0]=up[v][1][0]-(mx1[u].first==dif1[v]?mx1[u].second:mx1[u].first);
        }
    }
    for(auto v:adj[u])if(v!=p){
        if(p){
            int val=min(dp[v][1][1]+2,dp[v][0][0]+1);
            int val2=min(up[u][1][1]+2,up[u][0][0]+1);
            up[v][1][1]=dp[u][1][1]-val+val2;
            int mx=val2-min(up[u][0][1],up[u][0][0])-1;
            mx=max(mx,dif2[v]==mx2[u].first?mx2[u].second:mx2[u].first);
            up[v][0][1]=up[v][1][1]-mx;
        }else{
            int val=min(dp[v][1][1]+2,dp[v][0][0]+1);
            up[v][1][1]=dp[u][1][1]-val;
            up[v][0][1]=up[v][1][1]-(mx2[u].first==dif2[v]?mx2[u].second:mx2[u].first);
        }
    }
    for(auto v:adj[u])if(v!=p)dfs2(v,u);
    int res=dp[u][1][1];
    int mx=mx2[u].first;
    int val=min(up[u][1][1]+2,up[u][0][0]+1);
    res+=val;
    mx=max(mx,val-min(up[u][0][1],up[u][0][0])-1);
    ans=min(ans,res-mx);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(1);
    dfs2(1);
    cout << ans;
}