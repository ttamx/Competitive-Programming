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
    vector<vi> adj(n);
    vector<bool> ok(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        adj[p].emplace_back(i);
        if(p==0)ok[i]=true;
    }
    ok[0]=true;
    auto check=[&](int d){
        int cnt=0;
        vi dp(n);
        function<void(int)> dfs=[&](int u){
            for(auto v:adj[u]){
                dfs(v);
                dp[u]=max(dp[u],1+dp[v]);
            }
            if(dp[u]==d-1){
                if(!ok[u])cnt++;
                dp[u]=-1;
            }
        };
        dfs(0);
        return cnt;
    };
    int l=1,r=n-1;
    while(l<r){
        int m=(l+r)/2;
        if(check(m)<=k)r=m;
        else l=m+1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}