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
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> col(n,-1);
    function<bool(int)> dfs=[&](int u){
        for(auto v:adj[u]){
            if(col[v]==-1){
                col[v]=col[u]^1;
                if(!dfs(v))return false;
            }else{
                if(col[v]==col[u])return false;
            }
        }
        return true;
    };
    col[0]=0;
    if(dfs(0)){
        cout << "Bob" << endl;
        vector<vector<int>> id(2);
        for(int i=0;i<n;i++)id[col[i]].emplace_back(i);
        vector<int> all;
        for(int i=0;i<n;i++){
            int a,b;
            cin >> a >> b;
            for(auto v:{a,b}){
                bool ok=true;
                for(auto x:all){
                    if(x==v){
                        ok=false;
                    }
                }
                if(ok)all.emplace_back(v);
            }
            if(!id[0].empty()&&(a==all[0]||b==all[0])){
                cout << id[0].back()+1 << " " << all[0] << endl;
                id[0].pop_back();
                continue;
            }
            if(!id[1].empty()&&(a==all[1]||b==all[1])){
                cout << id[1].back()+1 << " " << all[1] << endl;
                id[1].pop_back();
                continue;
            }
            if(id[1].empty()){
                cout << id[0].back()+1 << " " << all[2] << endl;
                id[0].pop_back();
                continue;
            }
            if(id[0].empty()){
                cout << id[1].back()+1 << " " << all[2] << endl;
                id[1].pop_back();
                continue;
            }
            assert(false);
        }

    }else{
        cout << "Alice" << endl;
        for(int i=0;i<n;i++){
            cout << 1 << " " << 2 << endl;
            int x,c;
            cin >> x >> c;
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}