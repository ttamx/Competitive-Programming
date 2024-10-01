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
    int n,m;
    cin >> n >> m;
    vector<vector<ll>> dp(n,vector<ll>(n,LINF));
    vector<tuple<int,int,ll>> edges(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
        dp[u][v]=min(dp[u][v],w);
        dp[v][u]=min(dp[v][u],w);
    }
    for(int i=0;i<n;i++)dp[i][i]=0;
    for(int i=0;i<n;i++){
        for(int u=0;u<n;u++){
            for(int v=0;v<n;v++){
                dp[u][v]=min(dp[u][v],dp[u][i]+dp[i][v]);
            }
        }
    }
    int q;
    cin >> q;
    while(q--){
        int k;
        cin >> k;
        vector<int> a(k);
        for(auto &x:a){
            cin >> x;
            x--;
        }
        ll ans=LINF;
        do{
            for(int mask=0;mask<1<<k;mask++){
                int last=0;
                ll res=0;
                for(int i=0;i<k;i++){
                    auto [u,v,w]=edges[a[i]];
                    if(mask>>i&1){
                        res+=dp[last][u]+w;
                        last=v;
                    }else{
                        res+=dp[last][v]+w;
                        last=u;
                    }
                }
                res+=dp[last][n-1];
                ans=min(ans,res);
            }
        }while(next_permutation(a.begin(),a.end()));
        cout << ans << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}