#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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

void runcase(){
    int n;
    cin >> n;
    vector<vi> adj(n);
    for(int i=1;i<n;i++){
        int x;
        cin >> x;
        x--;
        adj[x].emplace_back(i);
    }
    vi dp(n),siz(n),ext(n);
    function<void(int)> dfs=[&](int u){
        siz[u]=1;
        int sum=0;
        pii mx(-1,0);
        for(auto v:adj[u]){
            dfs(v);
            int left=siz[v]-2*dp[v];
            sum+=left;
            mx=max(mx,pii(left,v));
            dp[u]+=dp[v];
            siz[u]+=siz[v];
        }
        if(mx.first<=sum/2){
            dp[u]+=sum/2;
        }else{
            int d=2*mx.first-sum;
            int ext=dp[u]-dp[mx.second];
            int p=min(d/2,ext);
            dp[u]+=sum-mx.first+p;
        }
    };
    dfs(0);
    cout << dp[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}