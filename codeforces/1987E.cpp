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
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    ll ans=0;
    vector<vector<ll>> dp(n,vector<ll>(n));
    function<void(int)> dfs=[&](int u){
        ll sum=0;
        int ch=0;
        for(auto v:adj[u]){
            ch++;
            dfs(v);
            sum+=a[v];
            for(int i=1;i<n;i++)dp[u][i]=min(dp[u][i]+dp[v][i-1],LINF);
        }
        if(ch>0){
            if(a[u]>sum){
                for(int i=1;i<n;i++){
                    ll used=min(dp[u][i],a[u]-sum);
                    ans+=used*i;
                    sum+=used;
                    if(dp[u][i]<LINF)dp[u][i]-=used;
                    if(sum==a[u])break;
                }
            }else{
                dp[u][0]=sum-a[u];
            }
        }else{
            dp[u][0]=LINF;
        }
    };
    dfs(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}