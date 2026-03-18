#include<bits/stdc++.h>

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
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        deg[v]++;
    }
    vector<int> p(n),q(n);
    for(auto &x:p){
        cin >> x;
        x--;
    }
    for(int i=0;i<n;i++){
        q[p[i]]=i;
    }
    int ans=0;
    vector<int> qu;
    vector<bool> mark(n);
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            qu.emplace_back(i);
        }
    }
    for(int i=0;i<n;i++){
        int u=q[i];
        if(!mark[u]){
            ans+=max((int)qu.size()-1,0);
            for(auto x:qu){
                mark[x]=true;
            }
            qu.clear();
        }
        for(auto v:adj[u]){
            if(--deg[v]==0){
                qu.emplace_back(v);
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}