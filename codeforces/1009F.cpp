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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
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
    vi ans(n);
    vi mx(n);
    vector<vi> comp(n);
    function<void(int,int)> dfs=[&](int u,int p){
        int cs=0;
        for(auto v:adj[u])if(v!=p){
            dfs(v,u);
            if(sz(comp[v])>cs){
                cs=sz(comp[v]);
                swap(comp[u],comp[v]);
                swap(mx[u],mx[v]);
            }
            int s=sz(comp[v]);
            for(int i=0;i<s;i++){
                comp[u][cs-1-i]+=comp[v].back();
                comp[v].pop_back();
            }
            for(int i=0;i<s;i++){
                if(comp[u][cs-1-i]>comp[u][cs-1-mx[u]]||(comp[u][cs-1-i]==comp[u][cs-1-mx[u]]&&i<mx[u])){
                    mx[u]=i;
                }
            }
        }
        if(comp[u].empty()||comp[u][cs-1-mx[u]]<=1)mx[u]=0;
        else mx[u]++;
        comp[u].emplace_back(1);
        ans[u]=mx[u];
    };
    dfs(0,-1);
    for(auto x:ans)cout << x << "\n";
}