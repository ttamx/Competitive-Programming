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
    vector<vi> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vi dp(n),pa(n);
    function<void(int,int)> dfs=[&](int u,int p){
        pa[u]=p;
        dp[u]=p!=-1?1+dp[p]:0;
        for(auto v:adj[u])if(v!=p)dfs(v,u);
    };
    dfs(0,-1);
    int rt=max_element(all(dp))-dp.begin();
    dfs(rt,-1);
    int u=max_element(all(dp))-dp.begin();
    int dia=dp[u];
    int h=(dia+1)/2;
    while(dp[u]>h)u=pa[u];
    if((dia+1)%4==0){
        cout << (dia+1)/2 << "\n";
        for(int i=0;i<(dia+1)/4;i++){
            cout << u+1 << " " << i*2+1 << "\n";
            cout << pa[u]+1 << " " << i*2+1 << "\n";
        }
    }else{
        cout << h+1 << "\n";
        for(int i=0;i<=h;i++)cout << u+1 << " " << i << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}