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
    vector<vi> adj(n);
    vector<tuple<int,int,int>> edge(m);
    vi col;
    for(auto &[u,v,c]:edge){
        cin >> u >> v >> c;
        u--,v--;
        col.emplace_back(c);
    }
    sort(all(col));
    col.erase(unique(all(col)),col.end());
    int k=col.size();
    vector<vi> comp(k);
    for(auto [u,v,c]:edge){
        c=lower_bound(all(col),c)-col.begin();
        adj[u].emplace_back(c);
        adj[v].emplace_back(c);
        comp[c].emplace_back(u);
        comp[c].emplace_back(v);
    }
    queue<pair<int,int>> q;
    int b,e;
    cin >> b >> e;
    b--,e--;
    q.emplace(0,b);
    vi vis(n),vis2(k);
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop();
        if(u==e)return void(cout << d << "\n");
        for(auto c:adj[u])if(!vis2[c]){
            vis2[c]=true;
            for(auto v:comp[c])if(!vis[v]){
                vis[v]=true;
                q.emplace(d+1,v);
            }
        }
    }
    cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}