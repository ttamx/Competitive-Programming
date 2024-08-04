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
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto ask=[&](int x){
        cout << "? " << x+1 << endl;
        int res;
        cin >> res;
        return res;
    };
    vector<int> par(n,-1),deg(n);
    function<void(int)> dfs=[&](int u){
        for(auto v:adj[u])if(v!=par[u]){
            deg[u]++;
            par[v]=u;
            dfs(v);
        }
    };
    dfs(0);
    int leaf=-1;
    for(int i=1;i<n;i++)if(deg[i]==0)leaf=i;
    for(int t=0;t<70;t++)if(ask(leaf))return void(cout << "! " << leaf+1 << endl);
    vector<bool> del(n);
    for(int t=0;t<70;t++){
        vector<int> q;
        for(int i=1;i<n;i++)if(deg[i]==0&&!del[i]){
            q.emplace_back(i);
            del[i]=true;
        }
        for(auto u:q)deg[par[u]]--;
    }
    for(int i=0;i<n;i++)if(deg[i]==0&&!del[i]){
        int u=i;
        vector<int> path;
        while(u!=-1&&deg[u]==0){
            path.emplace_back(u);
            u=par[u];
            if(u!=-1)deg[u]--;
        }
        if(!ask(path.back()))continue;
        while(u!=-1){
            path.emplace_back(u);
            u=par[u];
        }
        int l=0,r=path.size()-1;
        while(l<r){
            int m=(l+r)/2;
            if(ask(path[m])){
                r=m;
            }else{
                r=min(r+1,(int)path.size()-1);
                l=min(m+2,r);
            }
        }
        cout << "! " << path[l]+1 << endl;
        return;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}