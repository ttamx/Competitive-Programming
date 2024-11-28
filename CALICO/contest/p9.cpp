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
    int n=500;
    auto ask=[&](int x){
        cout << "SCAN " << x+1 << endl;
        int u;
        cin >> u;
        return u-1;
    };
    auto answer=[&](int x){
        cout << "SUBMIT " << x << endl;
        string s;
        cin >> s;
    };
    queue<int> q;
    vector<int> d(n,-1);
    vector<set<int>> adj(n);
    d[0]=0;
    q.emplace(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        while(adj[u].size()<3){
            int v=ask(u);
            if(v==n-1){
                answer(d[u]+1);
                return;
            }
            adj[u].emplace(v);
            adj[v].emplace(u);
        }
        for(auto v:adj[u]){
            if(d[v]==-1){
                d[v]=d[u]+1;
                q.emplace(v);
            }
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}