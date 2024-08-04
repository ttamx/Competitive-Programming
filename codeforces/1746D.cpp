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

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        adj[i].emplace_back(p);
        adj[p].emplace_back(i);
    }
    vector<ll> s(n),c(n),dp(n);
    for(auto &x:s)cin >> x;
    ll ans=0;
    c[0]=k;
    function<void(int,int)> dfs=[&](int u,int p){
        ans+=c[u]*s[u];
        dp[u]=s[u];
        int ch=0;
        for(auto v:adj[u])if(v!=p)ch++;
        if(!ch)return;
        int ea=c[u]/ch;
        int rem=c[u]%ch;
        vector<ll> vals;
        for(auto v:adj[u])if(v!=p){
            c[v]=ea;
            dfs(v,u);
            vals.emplace_back(dp[v]);
        }
        sort(vals.rbegin(),vals.rend());
        for(int i=0;i<rem;i++)ans+=vals[i];
        if(ch)dp[u]+=vals[rem];
    };
    dfs(0,-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}